/**
 * @file veorun.c
 * @brief VE program to load user application code
 */
#define _GNU_SOURCE
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h>
#include <string.h>
#include <signal.h>
#include <sched.h>

#include <veorun.h>
#include <veo_private_defs.h>

/* in veo_block.s */
extern void _veo_block(void *);
extern uint64_t _veo_call_kernel_function;

typedef struct {const char *n; void *v;} static_sym_t;
/* without generated static symtable, this weak version is used. */
__attribute__((weak)) static_sym_t _veo_static_symtable[] = {
	{.n = 0, .v = 0},
};

static cpu_set_t _veorun_all_cpu_mask;

void *_veorun_thread_init(void *arg)
{
	int cpu = (int)arg;
	sigset_t set;
	sigfillset(&set);
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	if (cpu >= 0) {
		cpu_set_t mask;
		CPU_ZERO(&mask);
		CPU_SET(cpu, &mask);
		sched_setaffinity(0, sizeof(mask), &mask);
	}
	_veo_block(0);
	return 0;
}

int64_t _veo_create_thread_helper(int cpu)
{
	int rv;
	pthread_t _t;
	pthread_attr_t _a;
	pthread_attr_init(&_a);
	pthread_attr_setdetachstate(&_a, PTHREAD_CREATE_DETACHED);
	pthread_attr_setstacksize(&_a, 0x4000000);
	/* to allow a child thread to run on any cores */
	cpu_set_t oldmask;
	sched_getaffinity(0, sizeof(oldmask), &oldmask);
	sched_setaffinity(0, sizeof(_veorun_all_cpu_mask),
		&_veorun_all_cpu_mask);
	rv = pthread_create(&_t, &_a, _veorun_thread_init, cpu);
	/* restore the affinity */
	sched_setaffinity(0, sizeof(oldmask), &oldmask);
	return rv;
}

int64_t _veo_load_library_helper(const char *name)
{
	return (intptr_t)dlopen(name, RTLD_NOW);
}

int64_t _veo_find_sym_helper(void *handle, const char *name)
{
	if (handle)
		return (intptr_t)dlsym(handle, name);
	if (_veo_static_symtable) {
		static_sym_t *t = _veo_static_symtable;
		while (t->n != NULL) {
			if (strcmp(t->n, name) == 0)
				return (int64_t)t->v;
			t++;
		}
	}
	return 0L;
}

int64_t _veo_alloc_buff(size_t size)
{
	return (intptr_t)malloc(size);
}

void _veo_free_buff(void *buff)
{
	free(buff);
}

void _veo_proc_exit(void)
{
	exit(0);
}

void _veorun_init_all_cpu_mask(void)
{
	int ncpu = 8;/* FIXME */
	CPU_ZERO(&_veorun_all_cpu_mask);
	for (int i = 0; i < ncpu; ++i) {
		CPU_SET(i, &_veorun_all_cpu_mask);
	}
}

int main(int argc, char *argv[])
{
	struct veo__helper_functions helpers = {
		.version = VEORUN_VERSION,
		.load_library = (uintptr_t)_veo_load_library_helper,
		.find_sym = (uintptr_t)_veo_find_sym_helper,
		.alloc_buff = (uintptr_t)_veo_alloc_buff,
		.free_buff = (uintptr_t)_veo_free_buff,
		.create_thread = (uintptr_t)_veo_create_thread_helper,
		.call_func = (uintptr_t)_veo_call_kernel_function,
		.exit = (uintptr_t)_veo_proc_exit,
	};
	_veorun_init_all_cpu_mask();
	_veo_block(&helpers);
	return 0;
}

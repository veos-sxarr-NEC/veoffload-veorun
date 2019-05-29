/**
 * @file veorun.c
 * @brief VE program to load user application code
 */
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h>
#include <string.h>
#include <signal.h>

#include <veorun.h>
#include <veo_private_defs.h>

/* in veo_block.s */
extern void _veo_block(void *);
extern uint64_t _veo_call_kernel_function;

typedef struct {char *n; void *v;} static_sym_t;
/* in dummy.c or the self-compiled generated static symtable */
extern static_sym_t *_veo_static_symtable;
extern void _init_static_symtable(void);

void *_veorun_thread_init(void *arg)
{
	sigset_t set;
	sigfillset(&set);
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	_veo_block(0);
	return 0;
}

int64_t _veo_create_thread_helper(void)
{
	int rv;
	pthread_t _t;
	pthread_attr_t _a;
	pthread_attr_init(&_a);
	pthread_attr_setdetachstate(&_a, PTHREAD_CREATE_DETACHED);
	rv = pthread_create(&_t, &_a, _veorun_thread_init, NULL);
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
	_init_static_symtable();
	_veo_block(&helpers);
	return 0;
}

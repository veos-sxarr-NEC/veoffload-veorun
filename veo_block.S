#include "veo_private_defs.h"
	.text
	.globl _veo_block
_veo_block:
	# prologue
	st %fp, 0x0(,%sp)
	st %lr, 0x8(,%sp)
	st %got, 0x18(,%sp)
	st %plt, 0x20(,%sp)
	or %fp, 0, %sp
	# block
_veo_do_block:
	ld %s63, 0x18(,%s14)
	lea %s62, NR_ve_sysve
	lea %s61, VE_SYSVE_VEO_BLOCK
	shm.l %s62, 0x0(%s63)
	shm.l %s61, 0x8(%s63)
	shm.l %s0, 0x10(%s63)
	## 0x18-0x28 are reserved for %s1-%s3
	## save the current sp
	shm.l %sp, 0x30(%s63)
	monc
	.globl _veo_call_kernel_function
_veo_call_kernel_function:
	nop
	# arguments are set on %s0 to %s7, address is set to %s12.
	bsic %lr, (,%s12)
        # restore %sp in case it was changed for args passing
        or %sp, 0, %fp
	br.l _veo_do_block

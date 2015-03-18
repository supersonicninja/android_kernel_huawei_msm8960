/*

 x86 function call convention, 64-bit:
 -------------------------------------
  arguments           |  callee-saved      | extra caller-saved | return
 [callee-clobbered]   |                    | [callee-clobbered] |
 ---------------------------------------------------------------------------
 rdi rsi rdx rcx r8-9 | rbx rbp [*] r12-15 | r10-11             | rax, rdx [**]

 ( rsp is obviously invariant across normal function calls. (gcc can 'merge'
   functions when it sees tail-call optimization possibilities) rflags is
   clobbered. Leftover arguments are passed over the stack frame.)

 [*]  In the frame-pointers case rbp is fixed to the stack frame.

 [**] for struct return values wider than 64 bits the return convention is a
      bit more complex: up to 128 bits width we return small structures
      straight in rax, rdx. For structures larger than that (3 words or
      larger) the caller puts a pointer to an on-stack return struct
      [allocated in the caller's stack frame] into the first argument - i.e.
      into rdi. All other arguments shift up by one in this case.
      Fortunately this case is rare in the kernel.

For 32-bit we have the following conventions - kernel is built with
-mregparm=3 and -freg-struct-return:

 x86 function calling convention, 32-bit:
 ----------------------------------------
  arguments         | callee-saved        | extra caller-saved | return
 [callee-clobbered] |                     | [callee-clobbered] |
 -------------------------------------------------------------------------
 eax edx ecx        | ebx edi esi ebp [*] | <none>             | eax, edx [**]

 ( here too esp is obviously invariant across normal function calls. eflags
   is clobbered. Leftover arguments are passed over the stack frame. )

 [*]  In the frame-pointers case ebp is fixed to the stack frame.

 [**] We build with -freg-struct-return, which on 32-bit means similar
      semantics as on 64-bit: edx can be used for a second return value
      (i.e. covering integer and structure sizes up to 64 bits) - after that
      it gets more complex and more expensive: 3-word or larger struct returns
      get done in the caller's frame and the pointer to the return struct goes
      into regparm0, i.e. eax - the other arguments shift up and the
      function's register parameters degenerate to regparm=2 in essence.

*/

<<<<<<< HEAD
=======
#include "dwarf2.h"
>>>>>>> cm-10.0

/*
 * 64-bit system call stack frame layout defines and helpers, for
 * assembly code (note that the seemingly unnecessary parentheses
 * are to prevent cpp from inserting spaces in expressions that get
 * passed to macros):
 */

#define R15		  (0)
#define R14		  (8)
#define R13		 (16)
#define R12		 (24)
#define RBP		 (32)
#define RBX		 (40)

/* arguments: interrupts/non tracing syscalls only save up to here: */
#define R11		 (48)
#define R10		 (56)
#define R9		 (64)
#define R8		 (72)
#define RAX		 (80)
#define RCX		 (88)
#define RDX		 (96)
#define RSI		(104)
#define RDI		(112)
#define ORIG_RAX	(120)       /* + error_code */
/* end of arguments */

/* cpu exception frame or undefined in case of fast syscall: */
#define RIP		(128)
#define CS		(136)
#define EFLAGS		(144)
#define RSP		(152)
#define SS		(160)

#define ARGOFFSET	R11
#define SWFRAME		ORIG_RAX

<<<<<<< HEAD
	.macro SAVE_ARGS addskip=0, norcx=0, nor891011=0
	subq  $9*8+\addskip, %rsp
	CFI_ADJUST_CFA_OFFSET	9*8+\addskip
	movq  %rdi, 8*8(%rsp)
	CFI_REL_OFFSET	rdi, 8*8
	movq  %rsi, 7*8(%rsp)
	CFI_REL_OFFSET	rsi, 7*8
	movq  %rdx, 6*8(%rsp)
	CFI_REL_OFFSET	rdx, 6*8
	.if \norcx
	.else
	movq  %rcx, 5*8(%rsp)
	CFI_REL_OFFSET	rcx, 5*8
	.endif
	movq  %rax, 4*8(%rsp)
	CFI_REL_OFFSET	rax, 4*8
	.if \nor891011
	.else
	movq  %r8, 3*8(%rsp)
	CFI_REL_OFFSET	r8,  3*8
	movq  %r9, 2*8(%rsp)
	CFI_REL_OFFSET	r9,  2*8
	movq  %r10, 1*8(%rsp)
	CFI_REL_OFFSET	r10, 1*8
	movq  %r11, (%rsp)
	CFI_REL_OFFSET	r11, 0*8
	.endif
=======
	.macro SAVE_ARGS addskip=0, save_rcx=1, save_r891011=1
	subq  $9*8+\addskip, %rsp
	CFI_ADJUST_CFA_OFFSET	9*8+\addskip
	movq_cfi rdi, 8*8
	movq_cfi rsi, 7*8
	movq_cfi rdx, 6*8

	.if \save_rcx
	movq_cfi rcx, 5*8
	.endif

	movq_cfi rax, 4*8

	.if \save_r891011
	movq_cfi r8,  3*8
	movq_cfi r9,  2*8
	movq_cfi r10, 1*8
	movq_cfi r11, 0*8
	.endif

>>>>>>> cm-10.0
	.endm

#define ARG_SKIP	(9*8)

<<<<<<< HEAD
	.macro RESTORE_ARGS skiprax=0, addskip=0, skiprcx=0, skipr11=0, \
			    skipr8910=0, skiprdx=0
	.if \skipr11
	.else
	movq (%rsp), %r11
	CFI_RESTORE r11
	.endif
	.if \skipr8910
	.else
	movq 1*8(%rsp), %r10
	CFI_RESTORE r10
	movq 2*8(%rsp), %r9
	CFI_RESTORE r9
	movq 3*8(%rsp), %r8
	CFI_RESTORE r8
	.endif
	.if \skiprax
	.else
	movq 4*8(%rsp), %rax
	CFI_RESTORE rax
	.endif
	.if \skiprcx
	.else
	movq 5*8(%rsp), %rcx
	CFI_RESTORE rcx
	.endif
	.if \skiprdx
	.else
	movq 6*8(%rsp), %rdx
	CFI_RESTORE rdx
	.endif
	movq 7*8(%rsp), %rsi
	CFI_RESTORE rsi
	movq 8*8(%rsp), %rdi
	CFI_RESTORE rdi
=======
	.macro RESTORE_ARGS rstor_rax=1, addskip=0, rstor_rcx=1, rstor_r11=1, \
			    rstor_r8910=1, rstor_rdx=1
	.if \rstor_r11
	movq_cfi_restore 0*8, r11
	.endif

	.if \rstor_r8910
	movq_cfi_restore 1*8, r10
	movq_cfi_restore 2*8, r9
	movq_cfi_restore 3*8, r8
	.endif

	.if \rstor_rax
	movq_cfi_restore 4*8, rax
	.endif

	.if \rstor_rcx
	movq_cfi_restore 5*8, rcx
	.endif

	.if \rstor_rdx
	movq_cfi_restore 6*8, rdx
	.endif

	movq_cfi_restore 7*8, rsi
	movq_cfi_restore 8*8, rdi

>>>>>>> cm-10.0
	.if ARG_SKIP+\addskip > 0
	addq $ARG_SKIP+\addskip, %rsp
	CFI_ADJUST_CFA_OFFSET	-(ARG_SKIP+\addskip)
	.endif
	.endm

	.macro LOAD_ARGS offset, skiprax=0
	movq \offset(%rsp),    %r11
	movq \offset+8(%rsp),  %r10
	movq \offset+16(%rsp), %r9
	movq \offset+24(%rsp), %r8
	movq \offset+40(%rsp), %rcx
	movq \offset+48(%rsp), %rdx
	movq \offset+56(%rsp), %rsi
	movq \offset+64(%rsp), %rdi
	.if \skiprax
	.else
	movq \offset+72(%rsp), %rax
	.endif
	.endm

#define REST_SKIP	(6*8)

	.macro SAVE_REST
	subq $REST_SKIP, %rsp
	CFI_ADJUST_CFA_OFFSET	REST_SKIP
<<<<<<< HEAD
	movq %rbx, 5*8(%rsp)
	CFI_REL_OFFSET	rbx, 5*8
	movq %rbp, 4*8(%rsp)
	CFI_REL_OFFSET	rbp, 4*8
	movq %r12, 3*8(%rsp)
	CFI_REL_OFFSET	r12, 3*8
	movq %r13, 2*8(%rsp)
	CFI_REL_OFFSET	r13, 2*8
	movq %r14, 1*8(%rsp)
	CFI_REL_OFFSET	r14, 1*8
	movq %r15, (%rsp)
	CFI_REL_OFFSET	r15, 0*8
	.endm

	.macro RESTORE_REST
	movq (%rsp),     %r15
	CFI_RESTORE r15
	movq 1*8(%rsp),  %r14
	CFI_RESTORE r14
	movq 2*8(%rsp),  %r13
	CFI_RESTORE r13
	movq 3*8(%rsp),  %r12
	CFI_RESTORE r12
	movq 4*8(%rsp),  %rbp
	CFI_RESTORE rbp
	movq 5*8(%rsp),  %rbx
	CFI_RESTORE rbx
=======
	movq_cfi rbx, 5*8
	movq_cfi rbp, 4*8
	movq_cfi r12, 3*8
	movq_cfi r13, 2*8
	movq_cfi r14, 1*8
	movq_cfi r15, 0*8
	.endm

	.macro RESTORE_REST
	movq_cfi_restore 0*8, r15
	movq_cfi_restore 1*8, r14
	movq_cfi_restore 2*8, r13
	movq_cfi_restore 3*8, r12
	movq_cfi_restore 4*8, rbp
	movq_cfi_restore 5*8, rbx
>>>>>>> cm-10.0
	addq $REST_SKIP, %rsp
	CFI_ADJUST_CFA_OFFSET	-(REST_SKIP)
	.endm

	.macro SAVE_ALL
	SAVE_ARGS
	SAVE_REST
	.endm

	.macro RESTORE_ALL addskip=0
	RESTORE_REST
<<<<<<< HEAD
	RESTORE_ARGS 0, \addskip
=======
	RESTORE_ARGS 1, \addskip
>>>>>>> cm-10.0
	.endm

	.macro icebp
	.byte 0xf1
	.endm

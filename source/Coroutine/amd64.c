//
//  amd64.c
//  File file is part of the "Coroutine" project and released under the MIT License.
//
//  Created by Samuel Williams on 10/5/2018.
//  Copyright, 2018, by Samuel Williams. All rights reserved.
//

#include "amd64.h"

// coroutine_context * coroutine_transfer(coroutine_context * current, coroutine_context * target)
asm(
	"\t.text\n"
	
	#if _WIN32 || __CYGWIN__ || __MACH__
	"\t.globl _coroutine_transfer\n"
	"_coroutine_transfer:\n"
	#else
	"\t.globl coroutine_transfer\n"
	"coroutine_transfer:\n"
	#endif
	
	/* Save caller state */
	"\tpushq %rbp\n"
	"\tpushq %rbx\n"
	"\tpushq %r12\n"
	"\tpushq %r13\n"
	"\tpushq %r14\n"
	"\tpushq %r15\n"
	/* Save caller stack pointer */
	"\tmovq %rsp, (%rdi)\n"
	/* Restore callee stack pointer */
	"\tmovq (%rsi), %rsp\n"
	/* Restore callee stack */
	"\tpopq %r15\n"
	"\tpopq %r14\n"
	"\tpopq %r13\n"
	"\tpopq %r12\n"
	"\tpopq %rbx\n"
	"\tpopq %rbp\n"
	/* Put the first argument into the return value */
	"\tmovq %rdi, %rax\n"
	/* We pop the return address and jump to it */
	"\tret\n"
);

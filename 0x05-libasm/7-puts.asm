BITS 64
global asm_puts	; EXPORT our 'asm_puts' function
extern asm_strlen
	section .text

	; size_t asm_puts(const char *str);
	; returns the difference between two strings
	;
	; edi <- const char str
	;
	; Return: printed len
asm_puts:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the current stack position

	push rdi
	call asm_strlen
	mov r15, rax
	pop rdi
	push rdi
	mov rax, 1
	mov rsi, [rsp]
	mov rdi, 1
	mov rdx, r15
	syscall

	mov rax, r15

	function_epilogue:
	pop rdi
	pop r15
	mov rsp, rbp; Restore previous stack frame
	pop rbp; Those two lines are equivalent to 'leave'
	ret	; return to address in the stack IP

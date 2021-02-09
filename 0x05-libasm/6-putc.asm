BITS 64
global asm_putc	; EXPORT our 'asm_putc' function

	section .text

	; size_t asm_putc(int c);
	; returns the difference between two strings
	;
	; edi <- int c
	;
	; Return: The diff of the last character
asm_putc:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the current stack position

	push rdi
	mov rax, 1
	mov rsi, rsp
	mov rdi, 1
	mov rdx, 1
	syscall

	mov rax, 1

	function_epilogue:
	pop rdi
	mov rsp, rbp; Restore previous stack frame
	pop rbp; Those two lines are equivalent to 'leave'
	ret		; return to address in the stack IP

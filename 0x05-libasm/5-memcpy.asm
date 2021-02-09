BITS 64
global asm_memcpy	; EXPORT our 'asm_memcpy' function

	section .text

	; void *asm_memcpy(void *dest, const void *src, size_t n);
	; returns the difference between two strings
	;
	; edi <- dest
	; esi <- src
	; edx <- n number that limits the data
	;
	; Return: The diff of the last character
asm_memcpy:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the current stack position

	push r15

	mov r15, 0
	while_notnull:
		cmp r15d, edx
		je function_epilogue
		mov cl, [esi + r15d]
		mov [edi + r15d], cl
		inc r15d
		jmp while_notnull

	function_epilogue:
	pop r15
	mov rsp, rbp; Restore previous stack frame
	pop rbp; Those two lines are equivalent to 'leave'
	ret	; return to address in the stack IP

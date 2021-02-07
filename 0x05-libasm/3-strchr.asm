BITS 64
global asm_strchr	; EXPORT our 'asm_strchr' function

	section .text

	; char *asm_strchr(const char *s, int c);
	; returns the c address if found
	;
	; edi <- const char s
	; esi <- int c
	;
	; Return: returns a pointer to the ocurrence of char c
asm_strchr:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the current stack position

	mov rax, 0
	mov rbx, 0
	mov cl, sil
	mov bl, [edi]
	cmp bl, cl
	je set_output
	while_notnull:
		inc edi
		mov bl, [edi]
		cmp bl, cl
		je set_output
		cmp bl, 0
		jne while_notnull

	function_epilogue:
	mov rsp, rbp; Restore previous stack frame
	pop rbp; Those two lines are equivalent to 'leave'
	ret	; return to address in the stack IP

set_output:
	mov eax, edi
	jmp function_epilogue

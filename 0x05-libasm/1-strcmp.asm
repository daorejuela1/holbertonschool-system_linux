BITS 64
global asm_strcmp	; EXPORT our 'asm_strcmp' function

	section .text

	; size_t asm_strcmp(const char *s1, const char *s2);
	; returns the difference between two strings
	;
	; edi <- const char s1
	; esi <- const chat s2
	;
	; Return: The diff of the last character
asm_strcmp:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the current stack position

	push r15
	mov bl, [edi]
	mov cl, [esi]
	sub bl, cl
	cmp bl, 0
	jne return_value
	while_notnull:
		inc edi ; increments s1
		inc esi ; increments s2
		mov bl, [edi]; gets the ascii value of s1
		mov cl, [esi]; gets the ascii value of s2
		mov r15b, cl ; backup s1 value
		sub bl, cl; gets the diff between s1 and s2
		cmp bl, 0; if bl is different than zero break
		jne return_value
		cmp r15b, 0 ; if not null terminator in s1 repeat
		jne while_notnull
	return_value:
	mov al, bl ; return value
	cmp al, 0
	je function_epilogue; dont divide zero by zero
	jg greater
	jl less

	function_epilogue:
	pop r15
	mov rsp, rbp; Restore previous stack frame
	pop rbp; Those two lines are equivalent to 'leave'
	ret		; return to address in the stack IP

greater:
	mov rax, 1
	jmp function_epilogue

less:
	mov rax, -1
	jmp function_epilogue

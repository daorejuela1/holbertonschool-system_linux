BITS 64
global asm_strlen	; EXPORT our 'asm_strlen' function

	section .text

	; size_t asm_strlen(const char *str);
	; returns the len of an str
	;
	; edi <- str
	;
	; Return: The len of the str
asm_strlen:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the stack position

	mov ebx, 0 ; initialized the counter
	mov cl, [edi]
	cmp cl, 0
	je return_value
	while_notnull:
		inc ebx ; increments the counter
		inc edi ; increments the len
		mov cl, [edi] ; gets the value
		cmp cl, 0 ; if not null terminator repeat
		jne while_notnull
	return_value:
	mov eax, ebx ; return value
	pop rbp
	ret		; return to address in the stack

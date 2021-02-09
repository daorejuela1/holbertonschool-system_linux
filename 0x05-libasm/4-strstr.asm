BITS 64
global asm_strstr	; EXPORT our 'asm_strstr' function

	section .text

	; char *asm_strstr(const char *haystack, const char *needle);
	; returns the c address if found
	;
	; edi <- const char haystack
	; esi <- const char  needle 
	;
	; Return: returns a pointer to the ocurrence of char needle
asm_strstr:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the current stack position

	push r9
	mov rax, 0
	mov rbx, 0
	mov cl, [edi]
	cmp cl, 0
	je function_epilogue
	mov r9b, [esi]
	cmp r9b, 0
	je function_epilogue
	while_notnull:
		mov cl, [edi]
		mov r9b, [esi + ebx]
		cmp cl, r9b
		je increase_needle
		jne reset
		continue_after_reset:
			inc edi
			mov cl, [edi]
			cmp cl, 0
			je function_epilogue
			jne while_notnull

	function_epilogue:
	pop r9
	mov rsp, rbp; Restore previous stack frame
	pop rbp; Those two lines are equivalent to 'leave'
	ret	; return to address in the stack IP

increase_needle:
	cmp ebx, 0
	je set_output
	continue_after_output:
		inc ebx
		mov r9b, [esi + ebx]
		cmp r9b, 0
		je function_epilogue
		jmp continue_after_reset

reset:
	mov rbx, 0
	mov rax, 0
	jmp continue_after_reset

set_output:
	mov eax, edi
	jmp continue_after_output

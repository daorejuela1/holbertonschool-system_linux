BITS 64
global asm_strcasecmp	; EXPORT our 'asm_strcasecmp' function

	section .text

	; size_t asm_strcasecmp(const char *s1, const char *s2);
	; returns the difference between two strings
	;
	; edi <- const char s1
	; esi <- const chat s2
	;
	; Return: The diff of the last character
asm_strcasecmp:
	push rbp ; saves base pointer into the stack
	mov rbp, rsp ; update base pointer to handle the current stack position

	push r15
	push rbx
	push rcx
	mov bl, [edi]
	mov cl, [esi]
	s1_check:
		cmp bl, 64
		jg s1_can_be_mayus
	s2_check:
		cmp cl, 64
		jg s2_can_be_mayus
	substraction:
	sub bl, cl
	cmp bl, 0
	jne return_value
	while_notnull:
		inc edi ; increments s1
		inc esi ; increments s2
		mov bl, [edi]; gets the ascii value of s1
		mov cl, [esi]; gets the ascii value of s2
		loop_s1_check:
			cmp bl, 64
			jg loop_s1_can_be_mayus
		loop_s2_check:
			cmp cl, 64
			jg loop_s2_can_be_mayus
		loop_substraction:
		mov r15b, cl ; backup s1 value
		sub bl, cl; gets the diff between s1 and s2
		cmp bl, 0; if bl is different than zero break
		jne return_value
		cmp r15b, 0 ; if not null terminator in s1 repeat
		jne while_notnull
	return_value:
	mov eax, ebx ; return value

	function_epilogue:
	pop rcx
	pop rbx
	pop r15
	mov rsp, rbp; Restore previous stack frame
	pop rbp; Those two lines are equivalent to 'leave'
	ret		; return to address in the stack IP

s1_can_be_mayus:
	cmp bl, 91
	jl s1_is_mayus
	jge s2_check

greater:
	mov eax, 1
	jmp function_epilogue

zero:
	mov eax, 0
	jmp function_epilogue

less:
	mov eax, -1
	jmp function_epilogue

s1_is_mayus:
	add bl, 20H
	jmp s2_check

s2_can_be_mayus:
	cmp cl, 91
	jl s2_is_mayus
	jge substraction

s2_is_mayus:
	add cl, 20H
	jmp substraction

loop_s1_can_be_mayus:
	cmp bl, 91
	jl loop_s1_is_mayus
	jge loop_s2_check

loop_s1_is_mayus:
	add bl, 20H
	jmp loop_s2_check

loop_s2_can_be_mayus:
	cmp cl, 91
	jl loop_s2_is_mayus
	jge loop_substraction

loop_s2_is_mayus:
	add cl, 20H
	jmp loop_substraction

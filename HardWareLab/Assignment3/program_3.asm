section .data
	enter: db "Enter string:", 0Ah
	len_enter: equ $-enter
	result: db "String after adding 'an' :", 0Ah
	len_result: equ $-result
	blank: db 10

	str_len: db 0
	str2_len: db 0
	flag: db 0
section .bss
	str: resb 100
	str2: resb 200
	char: resb 1
	temp: resb 1
	temp1: resb 1
section .text
	global _start:
_start:

reading:
	;;read string
	mov ecx,enter
	mov edx,len_enter
	call WRITE
	
	mov ebx,str
	call READSTRING

	mov ebx,str
	mov al,BYTE[str_len]
	mov BYTE[temp],al
	mov ecx,str2
check_for_vowels:
	cmp BYTE[temp],0
	je over
	jmp vowel
check_over:
	cmp BYTE[flag],0
	je same_letter
	
	mov BYTE[flag],0
	mov BYTE[ecx],'a'
	inc ecx
	mov BYTE[ecx],'n'
	inc ecx
	mov BYTE[ecx],32
	inc ecx
	add BYTE[str2_len],3
same_letter:
	mov al,BYTE[ebx]
	mov BYTE[ecx],al
	inc BYTE[str2_len]
	inc ebx
	inc ecx
	dec BYTE[temp]
	cmp BYTE[temp],0
	je over
	cmp BYTE[ebx],32
	jne same_letter 
	inc ebx
	dec BYTE[temp]
	mov BYTE[ecx],32
	inc ecx
	inc BYTE[str2_len]
	jmp check_for_vowels
vowel:
	cmp BYTE[ebx],'a'
	je set_flag
	cmp BYTE[ebx],'A'
	je set_flag
	
	cmp BYTE[ebx],'e'
	je set_flag
	cmp BYTE[ebx],'E'
	je set_flag
	
	cmp BYTE[ebx],'i'
	je set_flag
	cmp BYTE[ebx],'I'
	je set_flag
	
	cmp BYTE[ebx],'o'
	je set_flag
	cmp BYTE[ebx],'O'
	je set_flag
	
	cmp BYTE[ebx],'u'
	je set_flag
	cmp BYTE[ebx],'U'
	je set_flag
	jmp check_over
set_flag:
	mov BYTE[flag],1
	jmp check_over

over:
	mov ecx,result
	mov edx,len_result
	call WRITE
	
	mov ecx,str2
	movzx edx,BYTE[str2_len]
	call WRITE
	call NEWLINE
exit:
	mov eax,1
	mov ebx,0
	int 80h
;SUBROUTINES
WRITE:
	mov eax,4
	mov ebx,1
	int 80h
	ret
READ:
	mov eax,3
	mov ebx,0
	int 80h
	ret
NEWLINE:
	mov ecx,blank
	mov edx,1
	call WRITE
	ret
READSTRING:
	mov BYTE[str_len],0
read_character:
	push ebx
	mov ecx,char
	mov edx,1
	call READ
	pop  ebx
	
	cmp BYTE[char],10
	jne carry_on
	ret
carry_on:	
	inc BYTE[str_len]
	mov al,BYTE[char]
	mov BYTE[ebx],al
	add ebx,1
	jmp read_character


section .data
	hwmany: db "Enter number of stings : 	"
	lenhwmany: equ $-hwmany
	enter: db "Enter all the strings", 0Ah
	len_enter: equ $-enter
	result: db "String sorted: ", 0Ah
	len_result: equ $-result
	blank: db 0Ah
section .bss
	number: resd 1
	digit: resb 1
	
	strings: resb 100000
	tempstring: resb 100
	numstr: resd 1
section .text
	global _start:
_start:

reading:
	
	mov ecx,hwmany
	mov edx,lenhwmany
	call WRITE
	
	call GETANYNUMBER
	mov eax,DWORD[number]
	mov DWORD[numstr],eax
	cmp DWORD[numstr],0
		je exit
	
	mov ecx,enter
	mov edx,len_enter
	call WRITE
	
	mov eax,strings
	mov ecx,DWORD[numstr]
	call READSTRINGS
	
	
	mov eax, strings
	mov ebx, 100
	mov ecx, DWORD[numstr]
	call STRBUBBLESORT
	
	
	mov ecx, result
	mov edx, len_result
	call WRITE
   
	mov eax, strings
	mov ecx, DWORD[numstr]
	call PRINTSTRINGS

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

	
READSTRINGS:	
	mov edx,0 
get_string:
	cmp edx,ecx
	je got_strings
	
	pusha
	call READWORD
	popa
	
	inc edx
	add eax,100
	jmp get_string
got_strings:
	ret	
READWORD: 
	push eax
	mov ecx,eax
	mov edx,1
	call READ
	pop eax
	
	cmp BYTE[ecx],10
	je got_word
	
	inc eax
	jmp READWORD
got_word:
	mov BYTE[eax],0 

	
STRLEN:
	mov ecx,0
str_len_calculate_loop:
	cmp BYTE[eax],0
	je got_strlen
	
	inc ecx
	inc eax
	jmp str_len_calculate_loop
got_strlen:
	mov eax,ecx
	ret
	
STRCPY:
	mov dl,BYTE[ebx]
	mov BYTE[eax],dl
	
	cmp BYTE[eax],0
	je strcpy_done
	
	inc eax
	inc ebx
	jmp STRCPY
strcpy_done:
	ret

	
STRCMP:
	movzx ecx,BYTE[eax]
	movzx edx,BYTE[ebx]
	
	add ecx,256
	sub ecx,edx
	
	cmp ecx,256
	jne strcmp_done
	
	cmp edx,0
	je strcmp_done
	
	inc eax
	inc ebx
	jmp STRCMP
strcmp_done:
	mov eax,ecx
	ret

STRBUBBLESORT:
	mov edx,0
str_bubble_sort_loop:
	cmp edx,ecx
	je str_bubble_sort_done
	
	pusha
	sub ecx,edx
	call STRBUBBLEUP
	popa
	
	inc edx
	jmp str_bubble_sort_loop
str_bubble_sort_done:
	ret

STRBUBBLEUP:
	dec ecx
	mov edx,0
str_bubbleup_loop:
	cmp ecx,edx
	je str_bubble_up_done
	
	pusha
	add ebx,eax
	call STRCMP
	cmp eax,256
	popa
	
	jbe no_swap_or_increment
	
	pusha

	add ebx,eax
	
	push eax
	push ebx
	mov ebx,eax
	mov eax,tempstring
	call STRCPY
	pop ebx
	pop eax
	
	push eax
	push ebx
	call STRCPY
	pop ebx
	pop eax
	
	push eax
	push ebx
	mov eax,ebx
	mov ebx,tempstring
	call STRCPY
	pop ebx
	pop eax
	
	popa
	
no_swap_or_increment:
	inc edx
	add eax,100
	jmp str_bubbleup_loop
str_bubble_up_done:
	ret

	
PRINTSTRINGS:
	mov edx,0
print_strings_loop:
	cmp edx,ecx
	je print_strings_done
	
	pusha
	call PRINTS
	call NEWLINE
	popa
	
	inc edx
	add eax,100
	jmp print_strings_loop
print_strings_done:
	ret
	
PRINTS:
	push eax
	call STRLEN
	mov edx,eax
	pop eax
	
	mov ecx,eax
	call WRITE
	ret

GETANYNUMBER:
	mov DWORD[number],0
  getnumber:
	mov ecx,digit
	mov edx,1
	call READ

	cmp BYTE[digit],10                 ;is digit=newline
	jne carryon
	ret			   	   ;got the n digit number
  carryon:				   ;to change number from ascii
	sub byte[digit],30h
	mov eax,DWORD[number]
	mov ebx,10
	mul ebx
	
	movzx ebx,byte[digit]
	add eax,ebx
	mov DWORD[number],eax
	jmp getnumber


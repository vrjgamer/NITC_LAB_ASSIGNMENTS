section .data
	enter: db "Enter string:", 0Ah
	len_enter: equ $-enter
	search: db "Enter word to be searched:", 0Ah
	len_search: equ $-search
	occur: db "Number of occurences	:", 0Ah
	len_occur: equ $-occur
	blank: db 10

	str_len: db 0
	str1_len: db 0
	word_len: db 0
	freq: db 0
section .bss
	number: resd 1
	string: resb 10
	stringlen: resb 1
	
	str: resb 100
	char: resb 1
	words: resb 30
	temp: resb 1
	tempw: resb 1
section .text
	global _start:
_start:

	;;read a string
	mov ecx,enter
	mov edx,len_enter
	call WRITE
	
	mov ebx,str
	call READSTRING
	mov al,BYTE[str_len]
	mov BYTE[str1_len],al
	mov BYTE[temp],al
	
got_str:

	;read the word
	mov ecx,search
	mov edx,len_search
	call WRITE
	
	mov ebx,words
	call READSTRING
	mov al,BYTE[str_len]
	mov BYTE[word_len],al
	
	;get occurences
	mov ebx,str	
refresh_check:
	mov ecx,words
	mov al,BYTE[word_len]
	mov BYTE[tempw],al
	
	cmp BYTE[temp],0
	je print_occurrences
	mov al,BYTE[ebx]
	cmp al,BYTE[ecx]
	je check_for_next
	inc ebx
	dec BYTE[temp]
	jmp refresh_check
check_for_next:
	dec BYTE[temp]
	dec BYTE[tempw]
	cmp BYTE[tempw],0
	jne carryon
	inc BYTE[freq]
	inc ebx
	cmp BYTE[temp],0
	je print_occurrences
	jmp refresh_check
carryon:
	cmp BYTE[temp],0
	je print_occurrences
	inc ecx
	inc ebx
	mov al,BYTE[ebx]
	cmp al,BYTE[ecx]
	je check_for_next
	dec ebx
	inc BYTE[temp]
	jmp refresh_check
	
	
print_occurrences:
	mov ecx,occur
	mov edx,len_occur
	call WRITE
	
	movzx eax,BYTE[freq]
	call DISPLAYNUMBER
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
	
DISPLAYNUMBER:
  	mov BYTE[stringlen], 0
  	mov ebx, string
  	add ebx, 9           ;pointing to end of string
   convert_number:
	mov edx, 0
  	mov ecx, 10
  	div ecx
  
 	mov BYTE[ebx], dl
	add BYTE[ebx], 48  ;coverting the got digit to ascii equivalent
  
  	inc BYTE[stringlen]
  	cmp eax, 0
  	je convert_done
  	dec ebx
  	jmp convert_number
  convert_done:
  	mov ecx, ebx
  	movzx edx, BYTE[stringlen]
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
	

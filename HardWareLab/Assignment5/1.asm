section .data
msg1:db "Enter the number of strings",10
msg1_len:equ $-msg1
msg2:db "Enter the string:",10
msg2_len:equ $-msg2
msg3:db "The sorted strings set is:",10
msg3_len:equ $-msg3
newline:db 10
space:db 32


section .bss
strings:times 100 resb 100
temps:resb 100
len_array:resd 100
len_j:resd 1
len_j_1:resd 1
number:resd 1
flag:resb 1
temp:resb 1
a:resb 1
b:resb 1
mult:resd 1
i:resd 1
j:resd 1
nd:resb 1
count:resd 1
res:resd 1
verified: resd 1
num:resd 1
length:resd 1
currstart:resd 1


section .text
global _start
_start:


mov eax,4
mov ebx,1
mov ecx,msg2
mov edx,msg2_len
int 80h






;-----READ THE STRINGS-----------------------------------------------------------------------------------------------------------

mov dword[count],0
mov esi,strings
mov dword[mult],100

read_strings:

;locate the position
mov eax,dword[count]
mul dword[mult]
mov ebx,0
add ebx,esi
add ebx,eax
mov eax,0
mov byte[flag],0

;read the word
call readword

;the strings ends if =1
cmp byte[flag],1
je end_read_strings



mov edx,dword[count]
inc edx
inc dword[count]
jmp read_strings
end_read_strings:


mov edx,dword[count]
mov dword[number],edx
inc dword[number]

;-----------------------------------------------BUBBLE SORT-----------------------------------------------------------

mov dword[i],0
mov dword[j],0
mov esi,strings
mov edi,len_array

i_loop_start:
mov edx,dword[number]
dec edx
cmp dword[i],edx                ;i=0 to n-1
jnb i_loop_exit

i_loop_code:
mov dword[j],0


j_loop_start:
mov edx, dword[number]
sub edx,dword[i]
dec edx
cmp dword[j],edx
jnb j_loop_exit

j_loop_code:

mov eax,dword[j]

mul dword[mult]

mov ebx,esi
add ebx,eax
mov ecx,ebx

add ebx,dword[mult]
mov eax,ecx


call strcmp



mov ecx,dword[res]
cmp ecx,1
jne continue_j

call swap

continue_j:
inc dword[j]
jmp j_loop_start
j_loop_exit:




inc dword[i]
jmp i_loop_start
i_loop_exit:




;--------------------------------------------------------------------------------------------------------------------



mov eax,4
mov ebx,1
mov ecx,msg3
mov edx,msg3_len
int 80h


print_final:
;-----------PRINT THE STRINGS--------------------------------------------------------------------------------------------------------
mov esi,strings
mov dword[count],0

print_strings:

mov edx,dword[count]
cmp edx,dword[number]
jnb end_print_strings

mov eax,dword[count]
mul dword[mult]
mov ebx,0
add ebx,esi
add ebx,eax
mov eax,0
call printstring

inc dword[count]
jmp print_strings
end_print_strings:


pusha
mov eax,4
mov ebx,1
mov ecx,newline
mov edx,1
int 80h
popa

;------------------------------------------------------------------------------------------------------------------------------------


end:
mov eax,1
mov ebx,0
int 80h








;------------------------------------------------------------------------------------------------------------------------------------
;PRINTFUNCTION
printnum:
pusha
mov byte[nd],0
startprint:
mov eax,dword[num]
mov ecx,10
mov edx,0
div ecx
push edx
inc byte[nd]
mov dword[num],eax
cmp dword[num],0
je endprint
jmp startprint

endprint:
pop edx
mov byte[temp],dl
add byte[temp],30h
pusha
mov eax,4
mov ebx,1
mov ecx,temp
mov edx,1
int 80h
popa
dec byte[nd]
cmp byte[nd],0
je exitfunc
jmp endprint


exitfunc:
mov eax,4
mov ebx,1
mov ecx,newline
mov edx,1
int 80h
popa 
ret

;-----------------------------------------------------------------------------------------------------------------------------------
readstring:
pusha
mov eax,3
mov ebx,0
mov ecx,temp
mov edx,1
int 80h
popa
cmp byte[temp],10
je endreads
mov cl,byte[temp]
mov byte[ebx+eax],cl
inc eax
jmp readstring
endreads:
mov byte[ebx+eax],0
mov dword[length],eax
ret

;----------------------------------------------------------------------------------------------------------------------------------
printstring:
mov cl,byte[ebx+eax]
mov byte[temp],cl
cmp byte[temp],0
je endprints
pusha
mov eax,4
mov ebx,1
mov ecx,temp
mov edx,1
int 80h
popa
inc eax
jmp printstring
endprints:
pusha
mov eax,4
mov ebx,1
mov ecx,space
mov edx,1
int 80h
popa
ret





;READ FUNCTION---------------------------------------------------------------------------------------------------------------------
readnum:
pusha
mov dword[num],0
read:
mov eax,3
mov ebx,0
mov ecx,temp
mov edx,1
int 80h
cmp byte[temp],10
je endread
mov eax,dword[num]
mov ecx,10
mul ecx
sub byte[temp],30h
movzx ebx,byte[temp]
add eax,ebx
mov dword[num],eax
jmp read

endread:
popa
ret


;--------------------------STRCMP, PUT EAX=STR1 AND EBX=STR2--------------------------RET 1 IF STR1>STR2,0 IF EQUAL AND ,2 OTHERWISE -----------------------------------------

strcmp:
mov ecx,0
compare_loop:
mov dl,byte[eax+ecx]
cmp dl,0
je check_for_length
mov dl,byte[ebx+ecx]
cmp dl,0
je check_for_length

cmp dl,97
jnb continue_for_bxstring
add dl,32
continue_for_bxstring:

push ebx
mov bl,byte[eax+ecx]
mov byte[temp],bl
cmp bl,97
jnb continue_for_axstring
add bl,32
mov byte[temp],bl

continue_for_axstring:
pop ebx



cmp byte[temp],dl
ja ret1
cmp byte[temp],dl
jb ret2
inc ecx
jmp compare_loop

check_for_length:
mov edi,eax
call strlen
mov edx,dword[length]
mov edi,ebx
call strlen
mov ecx,dword[length]
cmp edx,ecx
je reteq
cmp edx,ecx
jb ret2
jmp ret1


ret1:
mov dword[res],1
ret

ret2:
mov dword[res],2
ret

reteq:
mov dword[res],0
ret


;------------SWAP EAX=STR1 EBX=STR2---------------------------------------------------------------------------------------------


swap:
push esi

;---TEMP<=EAX STRING-------------
mov esi,0
mov edx,temps
copyloop1:
mov cl,byte[eax+esi]
mov byte[edx+esi],cl
cmp cl,0
je copyloop1_end
inc esi
jmp copyloop1
copyloop1_end:

;---EAX<=EBX STRING-------------
mov esi,0
mov edx,eax
copyloop2:
mov cl,byte[ebx+esi]
mov byte[edx+esi],cl
cmp cl,0
je copyloop2_end
inc esi
jmp copyloop2
copyloop2_end:

;---EBX<=TEMP STRING-------------
mov esi,0
mov edx,temps
copyloop3:
mov cl,byte[edx+esi]
mov byte[ebx+esi],cl
cmp cl,0
je copyloop3_end
inc esi
jmp copyloop3
copyloop3_end:


pop esi
ret

;------------------------STRING LENGTH------------PUT STRING=EAX----------------------------------------------------------

strlen:
pusha
mov ecx,0
len_loop:
cmp byte[edi+ecx],0
je end_len_loop
inc ecx
jmp len_loop
end_len_loop:
mov dword[length],ecx
popa
ret




;-------------------------------readword----------------------------------------------------------------

readword:
pusha
mov eax,3
mov ebx,0
mov ecx,temp
mov edx,1
int 80h
popa
cmp byte[temp],32
je endreadw
cmp byte[temp],10
je endreadw_flag
mov cl,byte[temp]
mov byte[ebx+eax],cl
inc eax
jmp readword
endreadw:
mov byte[ebx+eax],0
mov dword[length],eax
ret

endreadw_flag:
mov byte[ebx+eax],0
mov dword[length],eax
mov byte[flag],1
ret






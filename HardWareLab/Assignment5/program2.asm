section .data
msg1:db "Row Count: ",0Ah
msg1_len:equ $-msg1
msg4:db "Column Count: ",0Ah
msg4_len:equ $-msg4
msg2:db "Enter elements of matrix one by one: ",0Ah
msg2_len:equ $-msg2
msg5:db "Transpose: ",10
msg5_len:equ $-msg5
msg3:db "Stop",10
msg3_len:equ $-msg3
newline:db 10
space: db 32



section .bss
array:resd 10000
trans:resd 10000
temps:resb 100
len_array:resd 100
len_j:resd 1
len_j_1:resd 1
m:resd 1
n:resd 1
number:resd 1
temp:resb 1
a:resb 1
b:resb 1
flag:resb 1
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
mov ecx,msg1
mov edx,msg1_len
int 80h


call readnum
mov eax,dword[num]
mov dword[m],eax


mov eax,4
mov ebx,1
mov ecx,msg4
mov edx,msg4_len
int 80h


call readnum
mov eax,dword[num]
mov dword[n],eax


mov eax,4
mov ebx,1
mov ecx,msg2
mov edx,msg2_len
int 80h




;matrix read
mov dword[i],0
mov dword[j],0
mov esi,array

i_loop_start:
mov edx,dword[m]
cmp dword[i],edx                
jnb i_loop_exit

i_loop_code:
mov dword[j],0


j_loop_start:
mov edx, dword[n]
cmp dword[j],edx
jnb j_loop_exit

j_loop_code:

mov eax,dword[i]
mul dword[n]
add eax,dword[j]
call readnum
mov edx,dword[num]
mov dword[esi+4*eax],edx


inc dword[j]
jmp j_loop_start
j_loop_exit:


inc dword[i]
jmp i_loop_start
i_loop_exit:


;transpose
mov dword[i],0
mov dword[j],0
mov esi,array
mov edi,trans

i_loop_start_2:
mov edx,dword[m]
cmp dword[i],edx                
jnb i_loop_exit_2

i_loop_code_2:
mov dword[j],0


j_loop_start_2:
mov edx, dword[n]
cmp dword[j],edx
jnb j_loop_exit_2

j_loop_code_2:

mov edx,0
mov eax,dword[i]
mul dword[n]
add eax,dword[j]
mov ecx,dword[esi+4*eax]

mov edx,0
mov eax,dword[j]
mul dword[m]
add eax,dword[i]
mov dword[edi+4*eax],ecx


inc dword[j]
jmp j_loop_start_2
j_loop_exit_2:

inc dword[i]
jmp i_loop_start_2
i_loop_exit_2:

mov eax,4
mov ebx,1
mov ecx,msg5
mov edx,msg5_len
int 80h




;print
mov dword[i],0
mov dword[j],0
mov esi,trans

i_loop_start_1:
mov edx,dword[n]
cmp dword[i],edx              
jnb i_loop_exit_1

i_loop_code_1:
mov dword[j],0


j_loop_start_1:
mov edx, dword[m]
cmp dword[j],edx
jnb j_loop_exit_1

j_loop_code_1:

mov eax,dword[i]
mul dword[m]
add eax,dword[j]
mov edx,dword[esi+4*eax]
mov dword[num],edx
call printnum


inc dword[j]
jmp j_loop_start_1
j_loop_exit_1:


pusha
mov eax,4
mov ebx,1
mov ecx,newline
mov edx,1
int 80h
popa



inc dword[i]
jmp i_loop_start_1
i_loop_exit_1:



end:
mov eax,1
mov ebx,0
int 80h






;Subroutines


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
mov ecx,space
mov edx,1
int 80h
popa 
ret

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


strcmp:
mov ecx,0
compare_loop:
mov dl,byte[eax+ecx]
cmp dl,0
je check_for_length
mov dl,byte[ebx+ecx]
cmp dl,0
je check_for_length
cmp byte[eax+ecx],dl
ja ret1
cmp byte[eax+ecx],dl
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




swap:
push esi
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








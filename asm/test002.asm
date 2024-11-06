assume cs:code
code segment
start:
	;安装
	mov ax,cs
	mov ds,ax
	mov si,offset display
	mov ax,0
	mov es,ax
	mov di,200h

	mov cx,offset displayend - offset display
	cld
	rep movsb
	
	;设置向量
	mov ax,0
	mov es,ax
	mov word ptr es:[7ch*4],200h
	mov word ptr es:[7ch*4+2],0

	mov ax,4c00h
	int 21h
	
display:
	mov ax,0b800h
	mov es,ax
	
	mov al,dh
	dec al
	mov ah,160
	mul ah			;得到行偏移,ax中存放
	mov dh,0
	dec dl
	add dl,dl		;得到列偏移,dx中存放
	add ax,dx
	mov di,ax
	
	mov ah,00010100b
s:
	cmp byte ptr ds:[si],0
	je over

	mov al,ds:[si]
	mov es:[di],ax
	inc si
	inc di
	inc di
	jmp short s
     over:	
	iret
displayend:
	nop

code ends
end start

assume cs:code

code segment
	start:	mov ax,0b800h
			mov es,ax
 			mov di,(1-1)*00a0h+2*(1-1)
			mov bl,00010000b
			mov cx,7
	    
		s:	push cx
			mov cx,80*5
		
	   s1:	mov byte ptr es:[di],' '
			mov es:[di+1],bl
			add di,2
			loop s1
			
			pop cx
			add bl,00010000b
			loop s
			
			mov ax,4c00h
			int 21h
code ends

end start

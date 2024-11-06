assume cs:code,ds:data

data segment
	     db 80 dup(0)
data ends

temp segment
	     db 8 dup(0)
temp ends

code segment
	start:    
	          mov  ax,0b800h
	          mov  es,ax
	          mov  ax,data
	          mov  ds,ax
	          mov  si,0
			
	          call scanf
			
	          call sum

	          call print
			
	          mov  ax,4c00h
	          int  21h
	
	print:    mov  dx,0
	          mov  ax,bp
	          push bx
	          push ds
	          push si
	          push cx
	          mov  bx,temp
	          mov  ds,bx
	          mov  si,0
	          mov  bx,10
	s9:       div  bx
	          add  dl,'0'
	          mov  ds:[si],dl
	          inc  si
	          mov  dl,0
	          cmp  ax,0
	          je   skip6
	          jmp  short s9
	skip6:    mov  cx,si
	
	          mov  di,(5-1)*00a0h+2*(1-1)
	s10:      dec  si
	          mov  al,ds:[si]
	          mov  es:[di],al
	          mov  byte ptr es:[di+1],2
	          add  di,2
	          loop s10
	          mov  byte ptr es:[di],' '
	          add  di,2
	          pop  cx
	          pop  si
	          pop  ds
	          pop  bx
	          add  si,2
	          ret
 	   		
 	   		
	
	sum:      mov  bp,0
	          mov  cx,si
	          mov  si,0
	s1:       mov  ax,0

	s2:       cmp  byte ptr ds:[si],' '
	          je   skip1
	          mov  bx,10
	          mul  bx
	          mov  bx,0
	          mov  bl,ds:[si]
	          sub  bl,'0'
	          add  ax,bx
	          inc  si
	          jmp  short s2
   	   		
	skip1:    mov  bx,ax
	          mul  bx
	          mul  bx
	          add  bp,ax
	          inc  si
	          cmp  si,cx
	          je   skip2
	          jmp  short s1
	skip2:    ret
			
	scanf:    mov  ah,0
	          int  16h
	          cmp  ah,1ch
	          je   break
	          cmp  ah,0eh
	          je   delete
	          mov  ds:[si],al
	          inc  si
	          call show
	          jmp  short scanf
			
	break:    mov  byte ptr ds:[si],' '
	          inc  si
	          ret
			
	delete:cmp  si,0
	          je   back1
	          mov  byte ptr ds:[si-1],' '
	          call show
	          dec  si
	back1:    jmp  short scanf
			
	show:     push si
	          push cx
	          mov  di,(3-1)*00a0h+2*(1-1)
	          mov  cx,si
	          mov  si,0
	s:        mov  al,ds:[si]
	          mov  es:[di],al
	          mov  byte ptr es:[di+1],2
	          inc  si
	          add  di,2
	          loop s
	          pop  cx
	          pop  si
	          ret
code ends

end start

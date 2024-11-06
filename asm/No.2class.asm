assume cs:code,ds:data

data segment
	     db "Jie1 "
	     dw 61,59,52,75,82,329,0
	     db "Jie2 "
	     dw 52,83,99,99,62,395,0
	     db "Jie3 "
	     dw 67,57,66,91,98,379,0
	     db "Jie4 "
	     dw 75,95,57,51,55,333,0
	     db "Jie5 "
	     dw 75,80,83,59,66,363,0
	     db "Jie6 "
	     dw 70,80,65,83,86,384,0
	     db "Jie7 "
	     dw 67,79,86,84,75,391,0
	     db "Jie8 "
	     dw 64,62,73,78,81,358,0
	     db "Jie9 "
	     dw 90,68,83,79,64,384,0
	     db "Jie10"
	     dw 78,63,60,76,98,375,0
	     db "Jie11"
	     dw 69,82,76,87,94,408,0
	     db "Jie12"
	     dw 54,64,73,72,79,342,0
	     db "Jie13"
	     dw 95,94,74,67,66,396,0
	     db "Jie14"
	     dw 76,92,60,73,77,378,0
	     db "Jie15"
	     dw 85,60,69,87,56,357,0
	     db "Jie16"
	     dw 73,73,90,53,78,367,0
	     db "Jie17"
	     dw 94,74,70,88,80,406,0
	     db "Jie18"
	     dw 74,84,98,94,96,446,0
	     db "Jie19"
	     dw 98,65,89,64,51,367,0
	     db "Jie20"
	     dw 85,51,74,82,77,369,0
	     db "Jie21"
	     dw 92,60,58,91,99,400,0
	     db "Jie22"
	     dw 65,84,64,81,77,371,0
	     db "Jie23"
	     dw 86,59,90,57,68,360,0
	     db "Jie24"
	     dw 75,66,54,74,73,342,0
	     db "Jie25"
	     dw 79,89,99,65,91,423,0
	     db "Jie26"
	     dw 68,99,88,55,61,371,0
	     db "Jie27"
	     dw 51,59,70,63,55,298,0
	     db "Jie28"
	     dw 64,68,67,56,68,323,0
	     db "Jie29"
	     dw 73,69,62,59,77,340,0
	     db "Jie30"
	     dw 94,50,50,73,60,327,0
data ends

temp segment
	     db 16 dup(0)
temp ends

code segment
	start: mov  ax,data
	       mov  ds,ax
	       mov  dx,0
	       mov  bp,0
			
	       mov  cx,6
	       mov  si,9
	       call find
			
	       mov  cx,3
	       mov  si,15
	       call find
			
	       call filter
					
	       call print
	
	       mov  ax,4c00h
	       int  21h
	
	print: mov  ax,0b800h
	       mov  es,ax
	       mov  di,(5-1)*00a0h+2*(1-1)
	
	       mov  bx,0
	       mov  cx,30
			
	s6:    cmp  word ptr ds:[bx+17],1
	       je   skip5
	       push cx
	       push di
	   		
	       mov  si,0
	       mov  cx,5
	s7:    mov  al,ds:[bx+si]
	       mov  es:[di],al
	       mov  byte ptr es:[di+1],2
	       inc  si
	       add  di,2
	       loop s7
	       mov  byte ptr es:[di],' '
	       add  di,2
	   		
	       mov  cx,6
	s8:    mov  ax,ds:[bx+si]
	       push bx
	       push ds
	       push si
	       push cx
	       mov  bx,temp
	       mov  ds,bx
	       mov  si,0
	       mov  bl,10
	s9:    div  bl
	       add  ah,'0'
	       mov  ds:[si],ah
	       inc  si
	       mov  ah,0
	       cmp  al,0
	       je   skip6
	       jmp  short s9
	skip6: mov  cx,si
	
	s10:   dec  si
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
	       loop s8
			
	       pop  di
	       pop  cx
	       add  di,160
	skip5: add  bx,19
	       loop s6
	       ret
			
	filter:mov  bx,0
	       mov  cx,30
	s5:    cmp  [bx+9],dx
	       jb   skip4
	       cmp  [bx+15],bp
	       jb   skip4
	back1: add  bx,19
	       loop s5
	       ret
	       nop
	       nop
	skip4: mov  word ptr [bx+17],1
	       jmp  short back1
		
	
	
	

	find:  
	s1:    push cx
	       mov  ax,0
	       mov  bx,0
	       mov  cx,30
	s2:    cmp  word ptr ds:[bx+17],0
	       ja   skip1
	       cmp  ds:[bx+si],ax
	       jna  skip1
	       mov  ax,ds:[bx+si]
	skip1: add  bx,19
	       loop s2
	       mov  bx,0
	       mov  cx,30
	s3:    cmp  word ptr ds:[bx+17],0
	       ja   skip2
	       cmp  ds:[bx+si],ax
	       je   skip3
	skip2: add  bx,19
	       loop s3
	skip3: mov  word ptr ds:[bx+17],1
	       pop  cx
	       loop s1
			
	       mov  bx,0
	       mov  cx,30
	s4:    mov  word ptr ds:[bx+17],0
	       add  bx,19
	       loop s4
			
	       cmp  dx,0
	       ja   ret1
	       mov  dx,ax
	       ret
	ret1:  mov  bp,ax
	       ret
			 	
code ends


end start

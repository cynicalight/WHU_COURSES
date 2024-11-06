assume cs:code,ds:data

data segment
	     db " --z-j-- ",0
	     db "-       -",0
	     db "- -|-|- -",0
	     db "|-|   |-|",0
data ends

code segment
	start:mov  ax,0b800h
	      mov  es,ax
	      mov  di,(5-1)*00a0h+2*(1-1)
			
	      mov  ax,data
	      mov  ds,ax
	      mov  si,0
			
	      mov  cx,20
	s:    push cx
	      push di
	      mov  si,0
	      mov  cx,40
	    	
	s1:   mov  al,ds:[si]
	      inc  si
	      cmp  al,0
	      je   t1
	      mov  byte ptr es:[di+1],2
	      mov  es:[di],al
	      add  di,2
	 	   	
	back: nop
	      loop s1
	 
	 
	 
	      mov  cx,10000
	p1:   push cx
   			
	      mov  cx,50
	p2:   nop
	      loop p2
			
	      pop  cx
	      loop p1
			
	      pop  di
	      push di
	      mov  si,0
	      mov  cx,40
	s0:   mov  al,ds:[si]
	      inc  si
	      cmp  al,0
	      je   t2
	      mov  byte ptr es:[di+1],0
	      mov  byte ptr es:[di],' '
	      add  di,2
	   	    
	back1:nop
	      loop s0
			
	      pop  di
	      add  di,2
	      pop  cx
	      loop s
			
	      mov  ax,4c00h
	      int  21h
			
	t1:   add  di,160-18
	      jmp  short back
	 		
	t2:   add  di,160-18
	      jmp  short back1
	 		
code ends

end start

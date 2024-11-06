assume cs:code
data segment
  db "welcome to masm!",0
data ends
code segment
start:
	;调用显示
	mov dh,10		;行号
	mov dl,10		;列号
	mov cl,2
	mov ax,data
	mov ds,ax
	mov si,0h
	int 7ch

	mov ax,4c00h
	int 21h
	
code ends
end start

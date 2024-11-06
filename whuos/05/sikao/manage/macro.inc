%macro InitDescriptor 2
	mov	ax, cs
	movzx	eax, ax
	shl	eax, 4
	add	eax, %1
	mov	word [%2 + 2], ax
	shr	eax, 16
	mov	byte [%2 + 4], al
	mov	byte [%2 + 7], ah
%endmacro

%macro PrintStr 1
    	push 	%1
    	call 	DispStr
    	add 	esp, 4
%endmacro

%macro PrintInt 1
   	push 	%1
    	call 	DispInt
    	add 	esp, 4
%endmacro

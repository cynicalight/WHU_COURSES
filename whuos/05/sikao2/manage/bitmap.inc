; -------------------------------------------
; bitmap 位图法
; CheckVaild 检查第 eax 个页是否空闲 返回 ebx=1 表示未被分配
; SetBusy 设置第 eax 个页为忙碌 如果出错 ebx=0
; SetFree 设置第 eax 个页为空闲
; -------------------------------------------

CheckValid:
	push	ds
	push	eax
	push	ecx

	mov	ecx, eax; 暂存 eax

	mov	eax, ecx
	shr	eax, 3;	除以8,页号在bitmap中的哪个字节
	test	eax, 0FFFFFFC0h; 看看有没有超过64
	jz	.inmap; test出来0说明在64byte以内，合法
	jmp	.outmap

.inmap:
	mov 	ebx, BitMap
	;xchg	bx, bx	
    	mov 	bl, byte [ebx + eax] ; BitMap中的该字节
	;xchg	bx, bx	
    	and 	cl, 07h	; 页数的低3位，表示这个数字在bitmap某个字节中第几位
    	mov 	eax, 1
    	shl 	eax, cl ; 这个页对应的比特位
    	test 	bl, al ; ebx & eax 测试这一位是否为 1
    	jz 	.ok ; 为 0 表明未被分配

.outmap:
	mov	ebx, 0
	jmp	.exit


.ok:
	mov	ebx, 1
	jmp	.exit


.exit:
	pop	ecx
	pop	eax
	pop	ds
	ret



SetBusy:
	push	ds
	push	eax
	push	ecx
	push	edx

	mov	ecx, eax

	mov	eax, ecx
	
	shr	eax, 3;	除以8,页号在bitmap中的哪个字节
	test	eax, 0FFFFFFC0h; 看看有没有超过64
	jz	.inmap; test出来0说明在64byte以内，合法
	jmp	.outmap

.inmap:
	mov 	ebx, BitMap
    	mov	edx, ecx
	and	ecx, 07h
	mov 	edx, 1
	shl	edx, cl
	or	byte [ebx + eax], dl; 把那一位标记成1
	jmp	.exit
	
.outmap:
	mov	ebx, 0

.exit:
	pop	edx
	pop	ecx
	pop	eax
	pop	ds
	ret



SetFree:	; 这里输入eax为物理地址
	;xchg	bx, bx
	push	ds
	push	eax
	push	ebx
	push	ecx
	push	edx
	
	mov	eax, ebx
	mov	ecx, eax

	mov	eax, ecx

	shr	eax, 12; 除以4096
	
	shr	eax, 3;	除以8,页号在bitmap中的哪个字节
	test	eax, 0FFFFFFC0h; 看看有没有超过64
	jz	.inmap; test出来0说明在64byte以内，合法
	jmp	.outmap

.inmap:
	mov 	ebx, BitMap
    	mov	edx, ecx
	and	ecx, 07h
	mov 	edx, 1
	shl	edx, cl
	
	mov	ecx, 0FFFFFFFFh
	sub	ecx, edx; 那一位标记成一堆1中的0
	and	byte [ebx + eax], cl;

	jmp	.exit
	
.outmap:
	mov	ebx, 0

.exit:
	pop	edx
	pop	ecx
	pop 	ebx
	pop	eax
	pop	ds
	ret
	


	
	

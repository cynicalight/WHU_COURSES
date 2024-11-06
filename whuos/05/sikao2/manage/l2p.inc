;=========================================================
;LinearToPhysics:eax输入线性地址，ebx输出物理地址, ecx=1报错
;=========================================================

LinearToPhysics:
	push	ds
	push	es
	push	eax
	push	edx
	
	mov 	ecx, eax; 暂存eax
	
	mov 	eax, ecx
	mov	ebx, cr3

	;xchg 	bx, bx

	shr	eax, 22; 准备拿高10位出来
	and	eax, 03FFh; 清空其他位
	shl	eax, 2; 左移2位，4字节
	mov 	ebx, [ebx + eax]

	;xchg 	bx, bx		
	
	test	ebx, PG_P
	jz	.error; 页目录缺失

	and 	ebx, 0FFFFF000h; 高20位是基址
    	; 获取页地址
    	mov 	eax, ecx
    	shr 	eax, 12
    	and 	eax, 03FFh
    	shl	eax, 2
    	mov 	ebx, [ebx + eax]

	;xchg 	bx, bx

    	test 	ebx, PG_P
    	jz 	.error; 页表缺失
	
	and 	ebx, 0FFFFF000h
	and	ecx, 0FFFh; 低12位是偏移
	add	ebx, ecx

	;xchg 	bx, bx

	jmp	.exit

.error:
	mov	ecx, 01h

.exit:
	pop edx
    	pop eax
    	pop es
    	pop ds
    	ret





ShowResult:
	push	eax
	push	ecx
	
	push	eax
	PrintStr	strLinear	; 打印LinearAddr
	pop	eax
	
	push	eax			; 打印线性地址数字
	call	DispInt
	pop	eax

	call	LinearToPhysics
	cmp	ecx, 1			; 检查是否错误地址
	jnz	.c
	PrintStr	strError
	jmp	.exit
.c:
	PrintStr	strPhysics	;
	push	ebx
	call	DispInt
	pop	ebx			; 打印对应物理地址
	;call	DispReturn
.exit:
	call	DispReturn
	pop	ecx
	pop	eax
	ret

	

	
	

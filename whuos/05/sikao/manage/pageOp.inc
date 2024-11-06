; ------------------------------------------
; alloc_pages 给 eax 开始连续 ecx 个页的虚拟内存分配物理地址
; link_page 把第 ebx 个物理页分配给 eax 这个虚拟地址
; free_pages 释放虚拟地址 eax 对应的 ecx 个字节
; stop_page 把虚拟地址 eax 对应的页释放出来
; -------------------------------------------

alloc_pages:	; 	给eax起后面分配ecx页的物理地址
	
	push 	eax
    	mov 	edx, ecx 			; edx = 要请求的页数
    	mov 	ebx, 0
   	 					; 寻找连续的 ecx 个空闲页
	.for_map:				; 循环中的ebx表示在判断的页号, 从0开始
    		push 	ebx
    		mov 	ecx, edx		; ecx=edx=请求的页数，循环ecx次就是找连续的ecx个页
    		.for_pages:	
       			push 	ebx
        		mov 	eax, ebx
        		call 	CheckValid	; 检查这个页是否空闲
			;xchg	bx, bx
        		test 	ebx, ebx 	; ebx 为 1 表示 Vaild
        		jz 	.fail		; ebx = 0则说明这个页不空闲，或者超出了BitMap的最大范围
        		pop 	ebx
        		inc 	ebx		; 找下一个页
        		loop 	.for_pages
    		jmp 	.suc 			; 找到了够用到区域！
    		.fail: 				; 有一个页不行
        		pop 	ebx
        		jmp 	.find_next
    		.find_next: 			; 找下一个
        		pop 	ebx
        		inc 	ebx
        		cmp 	ebx, 512	; BitMap里一共64*8=512个页，超过了就寄了
        		jne 	.for_map
    		jmp 	.no_mem			; 找不到咯，寄咯
    	.suc: 
		;xchg	bx, bx
        	pop 	ebx
        	jmp 	.suc_mem

.no_mem:
    	pop 	eax
    	mov 	ebx, 1 ; 表示错误
    	jmp 	.exit

.suc_mem:
    	pop 	eax
    	mov 	ecx, edx
    	; 将 ebx 开始的连续 ecx 个页分配给 eax
    	.alloc:
        	call 	link_page
        	inc 	ebx
        	add 	eax, 4096
        	loop 	.alloc
    	mov 	ebx, 0 ; 表示成功
    	jmp 	.exit

.exit:
    	mov 	eax, cr0
    	or 	eax, 80000000h
    	mov 	cr0, eax ; 恢复分页
    	ret



link_page:	;把第 ebx 个物理页分配给 eax 这个虚拟地址
	
	push	ds
	push	eax
	push	ebx
	push	ecx
	push	edx
	
	push	eax
	push	ebx
	mov	eax, ebx
	call	SetBusy
	pop	ebx
	pop	eax	; 写BitMap

	mov	ecx, eax; 暂存
	
	
	mov 	eax, ecx

	mov	edx, ebx; 暂存
	
	; 找 eax 这个虚拟地址对应的页在哪呢
	shr	eax, 22
	and	eax, 03ffh
	call 	alloc_PDE ; 如果不存在 则创建
	shl	eax, 2
	mov	ebx, cr3
	mov	ebx, [ebx + eax]; 找到页表
	
	and 	ebx, 0FFFFF000h
	
	mov 	eax, ecx
	shr	eax, 12
	and	eax, 03ffh
	shl	eax, 2
	
	shl	edx, 12; 重点，edx暂存了ebx，也就是第几个页
		       ; 用第几个页*4096，就是对应物理页得地址
	or	edx, PG_P | PG_USU | PG_RWW
	
	mov	[ebx + eax], edx

.exit:
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	pop	ds
	ret



free_pages:	; 释放 eax 开始的 ecx 个页
	push	ax
	push	ebx
	mov 	ebx, cr0
    	and 	ebx, 7FFFFFFFh
    	mov 	cr0, ebx ; 先关分页
	pop 	ebx

.release:
	call	stop_page
	add	eax, 4096
	loop	.release

.exit:
    	mov 	eax, cr0
    	or 	eax, 80000000h
    	mov 	cr0, eax ; 恢复分页
		pop 	ax
    	ret



stop_page:
	
	push	ds
	push	eax
	push	ebx
	push	ecx
	push	edx
	
	push 	ebx
    	call 	SetFree
    	pop 	ebx ; 写BitMap

	mov	ecx, eax; 暂存
	
	mov	eax, ecx
	mov	edx, ebx; 暂存

	; 找 eax 这个虚拟地址对应的页在哪呢
	shr	eax, 22
	and	eax, 03ffh
	
	shl	eax, 2
	mov	ebx, cr3
	mov	ebx, [ebx + eax]
	
	and 	ebx, 0FFFFF000h
	
	mov 	eax, ecx
	shr	eax, 12
	and	eax, 03ffh
	shl	eax, 2
	mov 	dword [ebx + eax], 0 ; 删除映射

.exit:
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	pop	ds
	ret

alloc_PDE: ; 初始化 PDE （传入 eax 是序号）
    	pusha
		push 	ax

    	mov 	edi, LastPDE
    	mov 	edx, [es:edi] ; 准备把这个送给 PDE
    
    	shl 	eax, 2 ; 每个 PDE 四个字节
    	mov 	ebx, cr3
    	mov 	ecx, [ebx + eax]
    	test 	ecx, PG_P
    	jz 	.ini ; 初始化 PDE
    	jmp 	.exit ; 已经有了，不用再分配
.ini:
    	mov 	[ebx + eax], edx
    	add 	edx, 4096
    	mov 	[es:edi], edx
.exit:
		pop 	ax
    	popa
	ret

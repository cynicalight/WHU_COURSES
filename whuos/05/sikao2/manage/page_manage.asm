global page_manage
global alloc_pages
global free_pages

%include 	"manage/pm.inc"
%include	"manage/macro.inc"	; 宏定义

; 字符串
szPMMessage:			db	"In Protect Mode now. ^-^", 0Ah, 0Ah, 0	; 进入保护模式后显示此字符串
szMemChkTitle:			db	"BaseAddrL BaseAddrH LengthLow LengthHigh   Type", 0Ah, 0; 进入保护模式后显示此字符串
szRAMSize			db	"RAM size:", 0
szReturn			db	0Ah, 0
strLinear			db	"LinearAddr:", 0
strPhysics			db	"PhysicsAddr:", 0
strError			db	"A Wrong Address!", 0
strFail			db	"Failed To Alloc!", 0
strSucc			db	"Succeeded To Alloc!", 0
strFree			db	"Succeeded To Free!", 0
; 变量
wSPValueInRealMode		dw	0
dwMCRNumber:			dd	0	; Memory Check Result
dwDispPos:			dd	(80 * 19 + 0) * 2	; 屏幕第 6 行, 第 0 列。
dwMemSize:			dd	0
ARDStruct:			; Address Range Descriptor Structure
	dwBaseAddrLow:		dd	0
	dwBaseAddrHigh:	dd	0
	dwLengthLow:		dd	0
	dwLengthHigh:		dd	0
	dwType:		dd	0
PageTableNumber		dd	0

MemChkBuf:	times	256	db	0

_BitMap: 
    ; 观察可以发现，我们实际使用的内存都在 0x00100000 内, 最多到flatrw的 0x0fffffh
    ; 不妨直接假定 1M 内的内存都是被分配的
    ; 1M ~ 2M 的内存是可分配的
    times 32 db 0FFh ; 32 * 8 * 4K = 1M
    times 32 db 00h
BitMap equ _BitMap - $$

_LastPDE: dd 0
LastPDE equ _LastPDE - $$

page_manage:
	; 下面显示一个字符串, 见macro.inc
	;mov	eax, 12348765h
	;call	ShowResult

	; 给12348000处分配3页
	mov 	eax, 12348000h
	mov 	ecx, 3
	call	alloc_pages
	test	ebx, ebx		; 检查是否出错
	jz	.succeed
	PrintStr	strFail
.succeed:
	PrintStr	strSucc
	
	mov	eax, 1234A765h
	call	ShowResult


	; 给02336000处分配1页
	mov 	eax, 02336000h
	mov 	ecx, 1
	call	alloc_pages
	test	ebx, ebx		; 检查是否出错
	jz	.succeed2
	PrintStr	strFail
.succeed2:
	PrintStr	strSucc
	
	mov	eax, 02336666h
	call	ShowResult


	; 释放00100000的3页(wuli)
	mov 	eax, 12348000h
	mov	ebx, 00100000h
	mov	ecx, 3
	call	free_pages
	PrintStr	strFree
	
	mov	eax, 1234A765h
	call	ShowResult


	; 给01111000处分配4页
	mov 	eax, 01111000h
	mov 	ecx, 4
	call	alloc_pages
	test	ebx, ebx		; 检查是否出错
	jz	.succeed3
	PrintStr	strFail
.succeed3:
	PrintStr	strSucc
	
	mov	eax, 01111111h
	call	ShowResult


	; 给12348000处分配1页
	mov 	eax, 12348000h
	mov 	ecx, 1
	;xchg	bx, bx
	call	alloc_pages
	test	ebx, ebx		; 检查是否出错
	jz	.succeed4
	PrintStr	strFail
.succeed4:
	PrintStr	strSucc
	
	mov	eax, 12348765h
	call	ShowResult

	jmp	.exit

.exit:
	; 到此停止
	ret



%include	"manage/lib.inc"	; 库函数
%include	"manage/l2p.inc"	; 线性到物理到转换
%include	"manage/bitmap.inc"	; 手搓位图法功能
%include	"manage/pageOp.inc"	; 页操作，包括alloc和free

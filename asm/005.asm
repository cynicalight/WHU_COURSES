; 定义数据段
data segment
    ; 定义七种彩虹颜色
    colors db 01h, 02h, 03h, 04h, 05h, 06h, 07h
data ends

; 定义代码段
code segment
    assume cs:code, ds:data

start:
    ; 设置初始颜色
    mov ah, 06h
    mov al, 0Fh
    int 10h

    ; 输出七种彩虹颜色条
    mov cx, 7
    mov si, 0
    mov di, 0
    mov bh, 0
    mov bl, colors[si]
loop1:
    ; 输出一行颜色
    mov ah, 09h
    mov al, 20
    mov cx, 80
    rep stosw

    ; 判断是否到达五行
    inc di
    cmp di, 5
    jne loop2

    ; 切换颜色
    inc si
    mov di, 0
   mov bh, 0
    mov bl, colors[si]
loop2:
    ; 延时一段时间
    mov cx, 10000h
delay:
    dec cx
    jnz delay

    ; 输出一行颜色
    mov ah, 09h
    mov al, bl
    mov cx, 80
    rep stosw

    ; 判断是否到达一屏幕
    inc di
    cmp di, 25
    jne loop2

    ; 返回到起始位置
    mov ah, 02h
    mov bh, 0
    mov dh, 0
    mov dl, 0
    int 10h

    ; 切换颜色
    inc si
    mov di, 0
    mov bh, 0
    mov bl, colors[si]
    loop1:

    ; 程序结束
    mov ah, 4Ch
    int 21h

code ends
end start
data SEGMENT
    hello  DB 'Hello World!$' ;注意要以$结束
data ENDS
code SEGMENT
    ASSUME CS:CODE,DS:DATA
start:
    MOV AX,data  ;将data首地址赋值给AX                
    MOV DS,AX    ;将AX赋值给DS,使DS指向data
    LEA DX,hello ;使DX指向hello首地址
    MOV AH,09h   ;给AH设置参数09H
    INT 21h      ;执行AH中设置的09H号功能。输出DS指向的DX指向的字符串hello
    MOV AX,4C00h ;给AH设置参数4C00h
    int 21h      ;调用4C00h号功能，结束程序
code ENDS
END start
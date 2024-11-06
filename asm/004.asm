include kcsj.mac 
data segment 
car0 db 32,32,32,32,32,32,247,32,’’ 
car2 db 32,219,219,219,219,219,219,219,’’ 
road db 80 DUP(220),’$’ 
row db 0 
column db 0 
data ends 
code segment 
assume ds:data,cs:code 
start: mov ax,data 
mov ds,ax 
mov es,ax

           mov cx,2000h ;让光标不闪动
           mov ah,01h
           int 10h





     s0: 
         clearsc 02h ;清屏和设置颜色
         mov dh,4
         mov dl,0
         mov bh,0
         mov ah,2
         int 10h
         showcolor 178,4
         outcar 9,road  ;显示道路


         mov cx,73

     S1:   push cx

           mov cl,0
           mov row,CL
           mov dh,row
           mov dl,column
           mov bh,0
           mov ah,2
           int 10h               
           outcar 9,car0
           inc row

           mov ah,0
           MOV DH,row
           MOV DL,column
           mov ah,2
           int 10h      
           outcar 9,car1
           inc row


           mov ah,0
           MOV DH,row
           MOV DL,column
           mov ah,2
           int 10h           
           outcar 9,car2
           inc row


           mov ah,0
           MOV DH,row
           MOV DL,column
           mov ah,2
           int 10h
           outcar 9,car3
           mov ah,1           ;16号中断
           int 16h
           jnz quit
           INC column


          longtime ;延时
          POP CX

          dec cx ;循环
          cmp cx,0
          jnz S1


     S2:
          clearsc 01h  ;清屏

          mov dh,10
          mov dl,0
          mov bh,0
          mov ah,2
          int 10h
          showcolor 178,6
          outcar 9,road


          mov column,0
          mov dh,6
          mov dl,0
          mov bh,0
          mov ah,2
          int 10h
          mov cx,73
    S3:
           push cx

           mov cl,6
           mov row,CL
           mov dh,row
           mov dl,column
           mov bh,0
           mov ah,2
           int 10h 
           outcar 9,car0
           inc row

           mov ah,0
           MOV DH,row
           MOV DL,column
           mov ah,2
           int 10h
           outcar 9,car1
           inc row


           mov ah,0
           MOV DH,row
           MOV DL,column
           mov ah,2
           int 10h
           outcar 9,car2
           inc row


           mov ah,0
           MOV DH,row
           MOV DL,column
           mov ah,2
           int 10h
           outcar 9,car3
           mov ah,1           ;16号中断
           int 16h
           jnz quit
           INC column


          longtime ;延时
          POP CX 

          dec cx  ;循环
          cmp cx,0
          jnz S3

          mov column,0
          clearsc 01h
          jmp S0

     quit:
          mov ah,4ch
          int 21h     
code ends 
end start
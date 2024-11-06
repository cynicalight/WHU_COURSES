
assume ds:data, es:table, cs:code 

 

data segment  

    db '1975','1976','1977','1978','1979','1980','1981','1982','1983'  

    db '1984','1985','1986','1987','1988','1989','1990','1991','1992'  

    db '1993','1994','1995' 

  ;以上是表示21年的21个字符串

    dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514  

    dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000  

  ;以上是表示21年 公司总收入的21个dword型数据

    dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226  

    dw 11542,14430,15257,17800

  ;以上是表示21公司雇员人数的21个Word型数据。

data ends  

 

table segment  

    db 21 dup ('year summ ne ?? ')  

table ends

 

code segment

start:

      ;初始化2个数据段，将ds指向data，es指向table

      mov ax,data

      mov ds,ax

      mov ax,table

      mov es,ax

      ;初始化偏址寄存器变量

      mov bx,0

      mov si,0

      mov di,0

      ;共21行，循环21次，初始化计数器

      mov cx,21  

  s: 

      ;写入年份

      mov ax,0[bx]            ;如看着别扭，改成mov ax, [bx+0] 

      mov es:0[si],ax

      mov ax,2[bx]

      mov es:2[si],ax

      ;写入空格

      mov al,20H

      mov es:4[si],al

      ;写入收入

      mov ax,84[bx]

      mov es:5[si],ax

      mov ax,86[bx]

      mov es:7[si],ax

      ;写入空格

      mov al,20H

      mov es:9[si],al

      ;雇员数

      mov ax,168[di]

      mov es:10[si],ax

      ;写入空格

      mov al,20H

      mov es:12[si],al

      ;人均收入，高16位送入dx，低16位送入ax

      mov ax,[bx+84]

      mov dx,[bx+86]

      ;用个bp变量存储除数，为以后实验考虑

      mov bp,[di+168]

      div bp                  ;16位除法指令

      mov es:13[si],ax        ;将商的结果（ax）写入table段中

      ;写入空格

      mov al,20H

      mov es:15[si],al

      ;bx、si、di变量的递增

      add bx,4                ;年份和总收入都是双字单元，故bx的递增量是4

      add si,16               ;table中每行是16个字节，偏移量为16

      add di,2                ;人数是字单元，故di的递增量是2

      loop s

     

      mov ax,4c00H

      int 21H

code ends

end start
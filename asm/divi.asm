assume cs:code

code segment
    start:  mov ax, 1000
            mov bh, 1
            div bh

            mov ax, 4c00h
            int 21h
code ends

end start
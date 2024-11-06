# 1. 先进行编译
gcc -o write write.c

# 2. 运行程序
./write
#Process 16591 opening FIFO O_WRONLY
#此时在另外一个终端上运行read程序……

# 3. 当在另一终端运行read程序之后：
#process write:the file's descriptor is 3
#Write date is hello world!, 13 bytes is write
#Process 16591 finished

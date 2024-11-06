# 1. 先进行编译
gcc -o read read.c

# 2. 在另一终端运行./write程序

# 3. 运行read程序
./read
#Process 16731 opening FIFO O_RDONLY
#process read:the file's descriptor is 3
#the read data is hello world!
#Process 16731 finished, 13 bytes read

# 4. 在另一终端查看./write程序输出结果

#静态编译以及使用file命令检查
gcc -static main.c -o main_static
file main_static

#动态编译以及使用file命令检查
#添加代码，使用 gcc 编译器编译 main.c 文件，生成一个动态链接的可执行文件， 指定输出文件名为 main_dynamic。


#添加代码，使用 file 命令检查 main_dynamic 文件的类型和属性。


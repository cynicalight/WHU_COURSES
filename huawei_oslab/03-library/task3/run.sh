#请添加代码；使用 gcc 编译器编译 lib/add.c 文件；生成位置无关代码（Position Independent Code）；生成共享库；指定包含头文件的目录（include）；输出文件名为 lib/libadd.so。

gcc -o main main.c -I./include -L./lib/ -ladd

#请添加代码，设置 LD_LIBRARY_PATH 环境变量，使其包含 ./lib 目录，以便运行时找到共享库 libadd.so；


./main 3 5

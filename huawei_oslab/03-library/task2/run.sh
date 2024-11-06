#添加代码，使用 gcc 编译器编译 lib/add.c 文件;只编译，不链接;指定包含头文件的目录(include);指定输出文件名为 lib/add.o。

ar -rsv lib/libadd.a lib/add.o
#添加代码，使用gcc编译 main.c 文件，指定包含头文件的目录 include 和库文件的目录 lib，并链接静态库 libadd.a，输出文件名为 main

./main 3 5

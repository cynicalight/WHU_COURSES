#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    if (argc != 4) {
        printf("Error: no correct param! Example: main 3 5\n");
        return 0;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    void *lib_handle;
    int (*add)();
    char *error;
    //请添加代码，以RTLD_LAZY模式，动态打开argv[3]所指向的动态库，返回值赋值给lib_handle


    if (!lib_handle) 
    {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    //请添加代码，获取lib_handle中的关键函数add的地址，并赋值给add


    printf("%d + %d = %d\n", a, b, add(a,b));

    return 0;
}

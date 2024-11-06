#include <stdio.h>
#include <stdlib.h>
#include <add.h>

int main(int argc,char *argv[])
{
    if (argc != 3) {
        printf("Error: no correct param! Example: main 3 5\n");
        return 0;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%d + %d = %d\n", a, b, add(a,b));

    return 0;
}

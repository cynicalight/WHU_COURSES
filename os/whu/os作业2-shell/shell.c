#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>

#define MAXLINE 80 /* The maximum length command */

int main(void)
{
    char* args[MAXLINE / 2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    char* line[MAXLINE];
    int line_count = 0;

    printf("welcome to 412osh\n");

    while (should_run)
    {
        printf("412osh> ");
        fflush(stdout);
        // args[arg_count] = (char*)malloc(MAXLINE * sizeof(char)); // 分配内存空间
        // scanf("%s", args[arg_count]);
        // printf("%s\n",args[arg_count]);

        // 改用fgets()
        line[line_count] = (char*)malloc(MAXLINE * sizeof(char));
        char tmpstr[MAXLINE];
        fgets(tmpstr, MAXLINE, stdin);
        strcpy(line[line_count], tmpstr);


        if (strcmp(line[line_count], "exit\n") == 0)
        {
            should_run = 0;
            break;
        }
        else if (strcmp(line[line_count], "history\n") == 0)
        {
            if (line_count == 0)
                printf("NO commands history.\n");
            else
                for (int i = line_count - 1; i>=0; i-- )
                {
                    printf("%d %s", i + 1, line[i]);
                }
            continue;
        }
        else if (strcmp(line[line_count], "!!\n")==0)
        {
            // printf("enter !!");
            strcpy(tmpstr, line[line_count-1]);
            strcpy(line[line_count], line[line_count-1]);
        }
        else if ( tmpstr[0] == '!' && isdigit(tmpstr[1]) && tmpstr[2] == '\n') 
        {
            // printf("enter !n \n");
            int n;
            n = tmpstr[1] - '0'; // 解析出整数 n
            if(n>line_count-1)
            {
                printf("No such command in history.\n");
                continue;
            }
            else
            {
                strcpy(tmpstr, line[n-1]);
                strcpy(line[line_count], line[n - 1]);
            }
        }


        char* token = strtok(tmpstr, " \n\0");
        int arg_count = 0;
        while (token != NULL && arg_count < MAXLINE)
        {
            // 分配内存空间，并将单词存储在 args 数组中
            args[arg_count] = (char*)malloc(strlen(token) + 1);
            strcpy(args[arg_count], token);

            // 移动到下一个单词
            token = strtok(NULL, " \n\0");
            arg_count++;
        }
        args[arg_count] = NULL; // 最后一个参数设置为 NULL
        line_count++;

        int should_wait = 1;
        if (arg_count > 0 && strcmp(args[arg_count - 1], "&") == 0) {
            should_wait = 0;
            args[arg_count - 1] = NULL; // 删除 & 符号
        }


        // 创建子进程
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) { // 子进程
            // 执行用户指定的命令
            execvp(args[0], args);
            perror("execvp"); // 如果执行失败，则输出错误信息
            exit(EXIT_FAILURE); // 子进程退出
        }
        else { // 父进程
            if (should_wait) {
                // 等待子进程退出
                waitpid(pid, NULL, 0);
            }
        }

    }
    printf("byebye");
    return 0;
}

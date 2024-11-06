#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 27
// 9 for row; 9 for column; 9 for palace

int sudoku[9][9] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
};

int flag = 1;


void* checkr(void* t)
{
    int arr_check[9] = { 0 };
    long tt;
    tt = (long)t;
    for (int i = 0; i < 9; i++)
    {
        arr_check[sudoku[tt][i] - 1] = 1;
    }
    for (int i = 0; i < 9; i++)
    {
        if (arr_check[i] == 0)
        {
            flag = 0;
            return 0;
        }
    }
    return 0;
}

void* checkc(void* t)
{
    int arr_check[9] = { 0 };
    long tt;
    tt = (long)t;
    for (int i = 0; i < 9; i++)
    {
        arr_check[sudoku[i][tt] - 1] = 1;
    }
    for (int i = 0; i < 9; i++)
    {
        if (arr_check[i] == 0)
        {
            flag = 0;
            return 0;
        }
    }
    return 0;
}

void* checkp(void* t)
{
    int arr_check[9] = { 0 };
    long tt;
    tt = (long)t;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arr_check[sudoku[tt / 3 * 3 + i][tt % 3 * 3 + j] - 1] = 1;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (arr_check[i] == 0)
        {
            flag = 0;
            return 0;
        }
    }
    return 0;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int rc;

    for (long i = 0; i < NUM_THREADS; i++)
    {
        printf("Creating thread no.%ld...\n", i);
        if (i < 9)
        {
            rc = pthread_create(&threads[i], NULL, checkr, (void*)i);
            if (rc) {
                printf("ERROR: return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
        }
        else if (i < 18)
        {
            pthread_create(&threads[i], NULL, checkc, (void*)i - 9);
        }
        else
        {
            pthread_create(&threads[i], NULL, checkp, (void*)i - 18);
        }
        pthread_join(threads[i], NULL);

        if (!flag)
        {
            printf("Not sudoku...\n");
            return 0;
        }
    }

    printf("It is sudoku!!!\n");
    return 0;


}
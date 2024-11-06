#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MAX 10

int main()
{
    int score[3][7] = { 54,64,73,72,79,342,0,74,84,98,94,96,446,0,76,92,60,73,77,378,0 };
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "db \"" << ch[j] << " " << "jie" << i * 3 + j + 1;
            if (i * 3 + j + 1 < 10)
                cout << "  ";
            else if (i * 3 + j + 1 < 100 && i * 3 + j + 1 > 9)
                cout << " ";
            cout << "\"" << endl;
            cout << "dw " << score[j][0] << "," << score[j][1] << "," << score[j][2] << endl;

        }
    }
}
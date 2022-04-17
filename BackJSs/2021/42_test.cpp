#include<iostream>
#include<time.h>

using namespace std;
#define MAX 10000000
void rec(int trial);

int main()
{
    clock_t start, finish;
    double duration;

    start = clock();
    int map[100][100] = { 0 };
    for (int i = 0; i < MAX; i++)
    {
        if (i % 1 == 0)
        {
            int nx = 0;
            int ny = 0;
            map[0][i % 100] = i / 3.0;
            map[1][i % 100] = i / 3.0;
            map[2][i % 100] = i / 3.0;
            map[3][i % 100] = i / 3.0;
            map[4][i % 100] = i / 3.0;
        }
    }

    finish = clock();

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%fÃÊ", duration);
    return 0;
}

void rec(int trial)
{
    if (trial < MAX)
    {
        trial++;
        rec(trial);
    }
    else
    {
        return;
    }
}
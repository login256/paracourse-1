#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

#define N 100000
#define CPUS 3

int *self_a[CPUS];
int self_n[CPUS];

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void devide(int *data, int n)
{
    int minv, maxv;
    minv = INT32_MAX;
    maxv = INT32_MIN;
#pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            int v = omp_get_thread_num();
            printf("%d from %d\n", i, v);
            minv = MIN(minv, data[i]);
            maxv = MAX(maxv, data[i]);
        }
        int step = ((long long)maxv - minv + 1 - 1) / CPUS + 1;
        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            int w = ((long long)data[i] - minv) / step;
            self_n[w]++;
        }
        #pragma omp for
        for (int i = 0; i < CPUS; i++)
        {
            self_a[i] = malloc(self_n[i] * sizeof(int));
            self_n[i] = 0;
        }
        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            int w = ((long long)data[i] - minv) / step;
            self_a[w][self_n[w]] = data[i];
            self_n[w]++;
        }
    }
}

int cmp(const void *fi, const void *se)
{
    int a = *(int *)fi;
    int b = *(int *)se;
    if (a < b)
    {
        return -1;
    }
    else if (a > b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void self_sort()
{
    for (int i = 0; i < CPUS; i++)
    {
        qsort(self_a[i], self_n[i], sizeof(int), cmp);
    }
}

void merge(int *data)
{
    int cnt = 0;
    for (int i = 0; i < CPUS; i++)
    {
        for (int j = 0; j < self_n[i]; j++)
        {
            data[cnt++] = self_a[i][j];
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int *data = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
    }
    devide(data, n);
    self_sort();
    merge(data);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", data[i]);
    }
    return 0;
}
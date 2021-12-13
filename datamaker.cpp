#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    srand(time(0));
    int n = 100000;
    char s[100] = "data.in";
    int maxv = 10000000;
    if (argc >= 2)
    {
        sscanf(argv[1], "%d", &n);
    }
    if (argc >=3)
    {
        sscanf(argv[2], "%s", s);
    }
    if (argc >=4)
    {
        sscanf(argv[3], "%d", &maxv);
    }
    auto file = fopen(s,"w");
    fprintf(file,"%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", rand() % maxv);
    }
    fclose(file);
    return 0;
}
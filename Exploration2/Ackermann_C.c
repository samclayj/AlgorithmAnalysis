#include <stdio.h>
#include <time.h>

#define INT long long int

INT Ackermann(INT m, INT n)
{
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return  Ackermann(m - 1, 1);
    } else {
        return Ackermann(m - 1, Ackermann(m, n - 1));
    }
    return Ackermann(m - 1, Ackermann(m, n - 1));
}

int main(int argc, char* argv[])
{
    int m = 0;
    int n = 0;
    
    printf("ENTER M AND N SEPARATED BY A SPACE: ");
    
    scanf("%d", &m);
    scanf("%d", &n);
    
    clock_t start = clock(), diff;
    INT r = Ackermann(m, n);
    printf("For Ackermann(%d,%d) the result is: %lli\n", m, n, r);
    diff = clock() - start;
    
    INT msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %lli seconds %lli milliseconds\n\n", msec/1000, msec%1000);
    
}//end main

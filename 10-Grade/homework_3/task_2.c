#include <stdio.h>

int main()
{
    unsigned long long int a = 2;
    unsigned long long int b = 1;
    unsigned long long int modA;
    unsigned long long int modB;
    unsigned long long int modSum;
    unsigned long long int c;
    unsigned long long int tempA;
    unsigned long long int tempB;
    int i;
    printf("%d\n", a);
    printf("%d\n", b);
    for(i = 1; i <= 98; i++)
    {
        tempA = a;
        tempB = b;
        if(a / 10000000000000000 > 0)
        {

            modA = a % 10000000000000000;
            modB = b % 10000000000000000;
            modSum = modA + modB;
            a /= 10000000000000000;
            b /= 10000000000000000;
            c = a + b;
            if (modSum / 100000000000000000 > 0)
            {
                c += 1;
                modSum = modSum % 10000000000000000;
            }
            printf("%d. %llu%llu \n", i, c, modSum);
            a = tempB;
            b = c*10000000000000000 + modSum;
        }
        else
        {
            c = a + b;
            printf("%d. %llu \n", i, c);
            a = tempB;
            b = c;
        }
    }
    return 0;
}

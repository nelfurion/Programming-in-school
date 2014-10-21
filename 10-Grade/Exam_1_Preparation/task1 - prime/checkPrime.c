#include <stdio.h>
#include <math.h>

int main()
{
    unsigned long long int num = 286839645281;
    int isPrime = 0;
    while(!isPrime)
    {
        isPrime = 1;
        if(num % 2 != 0)
        {
            unsigned long long int root = sqrt(num);
            unsigned long long int i;
            for(i = 2; i < root; i++)
            {
                if(num % i == 0)
                {
                    isPrime = 0;
                }
            }
            if(!isPrime)
                num++;
        }
        else
        {
            isPrime = 0;
            num++;
        }
    }
    printf("%llu\n", num);
    return 0;
}

#include <stdio.h>
#include <stdbool.h>

int main()
{
    bool prime = true;
    int count = 1;
    int num = 3;
    int j;
    while(true)
    {
        prime = true;
        if (count > 10)
        {
            break;
        }
        for(j = 2; j < num; j++)
        {
            if(num % j == 0)
            {
                prime = false;
            }
        }
        if(prime)
        {
            int num2 = num + 2;
            for(j = 2; j < num2; j++)
            {
                if(num2 % j == 0)
                {
                    prime = false;
                }
            }
            if (prime)
            {
                printf("(%d, %d)\n", num, num2);
                count++;
            }
        }
        num++;
    }
    return 0;
}

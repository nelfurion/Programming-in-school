#include <stdio.h>

int main()
{
    int i;
    for(i = 0; i <= 30000; i++)
    {
        if((i % 21 == 0) && (i % 2 != 0))
            printf("%d\n", i);
    }
    return 0;
}

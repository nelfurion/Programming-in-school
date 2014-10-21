#include <stdio.h>

int main()
{
    int num = 465;
    switch(num % 2 + num % 3 + num % 5)
    {
        case 0:
            printf("It divides.\n");
            break;
        default:
            printf("It doesn't divide.");
            break;
    }
    return 0;
}

#include<stdio.h>

int main()
{
    int i;
    int a;
    int B;

    a=97;
    do {printf("%d - %c \n",a,a);
    a++;} while (a<123);

    B=65;
    do {printf("%d - %c\n",B,B);
    B++;} while (B<91);

    i=48;
    do {printf("%d - %c \n",i,i);
    i++;} while(i<58);
    return 0;
}

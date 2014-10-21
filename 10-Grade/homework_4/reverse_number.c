#include <stdio.h>
#include <stdbool.h>

void reverse(int number)
{
    char output[100];
    char numberString[100];
    bool endsWithZero = false;
    int reversed = number % 10;
    number /= 10;
    if (reversed == 0)
    {
        endsWithZero = true;
    }
    while(number > 0)
    {
        reversed *= 10;
        reversed += number % 10;
        number /= 10;
    }
    itoa(reversed, numberString, 10);
    if (endsWithZero)
    {
        strcpy(output, "0");
        strcat(output, numberString);
    }
    else
    {
        strcpy(output, numberString);
    }
    printf("%s\n", output);
}

int main()
{
    unsigned long long int number;
    number = 5170984;
    reverse(number);
    number = 406567;
    reverse(number);
    number = 368750;
    reverse(number);
    number = 2369510;
    reverse(number);
    number = 2183293;
    reverse(number);
}

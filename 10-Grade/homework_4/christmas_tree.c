#include <stdio.h>

void printTree(int height)
{
    int row = 1;
    int i;
    int leaves = 1;
    for(i = 0; i < height; i++)
    {
        int j;
        for(j = 0; j < height - row; j++)
        printf(" ");
        for(j = 0; j < leaves; j++)
            printf("*");
            printf("\n");
        row++;
        leaves += 2;
    }
}

int main()
{
    int height;
    height = 4;
    printTree(height);
    height = 7;
    printTree(height);
    height = 11;
    printTree(height);
    return 0;
}

#include <stdio.h>
#include <math.h>

int main()
{
    int memory[100] = {001};
    int acumulator;
    int progCount = 0;

    while (1)
    {
        int instruction = memory[progCount];
        progCount += 1;

        int operation = instruction / 100;
        int cell = instruction % 100;

        int x = cell / 10;
        int y = cell % 10;

        switch (operation)
        {
            case 0:
                scanf("%d", &memory[cell]);
                break;
            case 1:
                acumulator = memory[cell];
                break;
            case 2:
                acumulator += memory[cell];
                break;
            case 3:
                if (acumulator < 0)
                    progCount += cell;
                break;
            case 4:
                acumulator *= pow(10, x);
                acumulator /= pow(10, y);
                break;
            case 5:
                printf("%d", memory[cell]);
                break;
            case 6:
                memory[cell] = acumulator;
                break;
            case 7:
                acumulator -= memory[cell];
                break;
            case 8:
                memory[99] = 800 + progCount;
                progCount = cell;
                break;
            case 9:
                return 0;
                break;
        }
    }
    return 0;
}

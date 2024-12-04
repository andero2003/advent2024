#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getNumLength(int num)
{
    int length = 0;
    while (num != 0)
    {
        num /= 10;
        length++;
    }
    return length;
}

int main()
{
    FILE *fptr;
    fptr = fopen("day3.txt", "r");

    int N = 19846; // char count
    int total = 0;

    char ch;

    char *str = (char *)malloc(N * sizeof(char));

    int i = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        str[i] = ch;
        i++;
    }

    for (int pointer = 0; pointer < N - 12; pointer++) // some sliding window type shit
    {
        if (str[pointer] == 'm' && str[pointer + 1] == 'u' && str[pointer + 2] == 'l' && str[pointer + 3] == '(')
        {
            // parse the numbers
            char *substring = (char *)malloc(9 * sizeof(char));
            for (int i = 0; i < 8; i++)
            {
                substring[i] = str[pointer + i + 4];
            }

            int num1, num2;
            if (sscanf(substring, "%d,%d)", &num1, &num2) == 2)
            {
                int lengths = getNumLength(num1) + getNumLength(num2) + 1; // 1 for comma

                // verify that a closing bracket is present
                if (str[pointer + 4 + lengths] == ')')
                {
                    // add the product to the total
                    total += num1 * num2;
                }
            }
        }
    }

    printf("total: %d\n", total);

    return 0;
}
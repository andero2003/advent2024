#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum_input_string(FILE *fptr)
{
    int sum = 0;
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        char *only_this = (char *)malloc(sizeof(char));
        only_this[0] = ch;
        sum += atoi(only_this);
    }

    fseek(fptr, 0, SEEK_SET);

    return sum;
}

int main()
{
    FILE *fptr;
    fptr = fopen("day9.txt", "r");

    int total = 94638; // sum_input_string(fptr);
    int *new_input = (int *)malloc(total * sizeof(int));
    printf("Total: %d\n", total);

    char ch;
    int new_input_counter = 0;
    int id = 0;
    int i = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        int count = atoi(&ch);
        for (int j = 0; j < count; j++)
        {
            if (i % 2 == 0)
            {
                new_input[new_input_counter] = id;
            }
            else
            {
                new_input[new_input_counter] = -1;
            }
            new_input_counter++;
        }
        if (i % 2 == 0)
            id++;
        i++;
    }

    // for (int k = 0; k < total; k++)
    // {
    //     printf("[%d]", new_input[k]);
    // }

    int start_pointer = 0, end_pointer = total - 1;
    while (start_pointer < end_pointer)
    {
        while (new_input[start_pointer] != -1)
            start_pointer++;
        while (new_input[end_pointer] == -1)
            end_pointer--;
        if (start_pointer < end_pointer)
        {
            new_input[start_pointer] = new_input[end_pointer];
            new_input[end_pointer] = -1;
        }
    }

    // printf("\n");
    // printf("New input: ");
    // for (int k = 0; k < total; k++)
    // {
    //     printf("[%d]", new_input[k]);
    // }

    unsigned long long checksum = 0;
    for (int k = 0; k < total; k++)
    {
        if (new_input[k] != -1)
        {
            unsigned long long result = k * new_input[k];
            checksum += result;
        }
        else
        {
            break;
        }
    }
    printf("\nChecksum: %llu\n", checksum);

    fclose(fptr);

    return 0;
}
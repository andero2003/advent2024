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

int gap_big_enough(int *new_input, int start_pointer, int block_length)
{
    int gap = 0;
    for (int i = start_pointer; i < start_pointer + block_length; i++)
    {
        if (new_input[i] == -1)
        {
            gap++;
        }
        else
        {
            break; // non-contiguous block
        }
    }
    if (gap >= block_length)
    {
        return 1;
    }
    return 0;
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

        // if reached non -1 at the end, go to the beginning of current ID
        int block_length = 1;
        while (new_input[end_pointer] == new_input[end_pointer - 1])
        {
            end_pointer--;
            block_length++;
        }

        // test all gaps between start_pointer and end_pointer
        int found = 0;
        for (int temp_start = start_pointer; temp_start < end_pointer; temp_start++)
        {
            if (gap_big_enough(new_input, temp_start, block_length))
            {
                printf("Gap found for block with ID %d, length %d at %d\n", new_input[end_pointer], block_length, temp_start);
                for (int i = 0; i < block_length; i++)
                {
                    new_input[temp_start + i] = new_input[end_pointer + i];
                    new_input[end_pointer + i] = -1;
                }
                found = 1;
                printf("New pointers: %d, %d\n", start_pointer, end_pointer);
                break;
            }
        }
        if (!found)
            end_pointer--;

        printf("Pointers after: %d, %d\n", start_pointer, end_pointer);
    }
    printf("Final input: ");
    for (int k = 0; k < total; k++)
    {
        printf("[%d]", new_input[k]);
    }
    printf("\n");
    unsigned long long checksum = 0;
    for (int k = 0; k < total; k++)
    {
        if (new_input[k] != -1)
        {
            unsigned long long result = k * new_input[k];
            checksum += result;
        }
    }
    printf("\nChecksum: %llu\n", checksum);

    fclose(fptr);

    return 0;
}
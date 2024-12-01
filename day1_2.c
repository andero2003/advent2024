#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    FILE *fptr;
    fptr = fopen("day1.txt", "r");

    int total_lines = 0;
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '\n')
        {
            total_lines++;
        }
    }

    int *col1 = (int *)malloc(total_lines * sizeof(int));
    int *col2 = (int *)malloc(total_lines * sizeof(int));

    fseek(fptr, 0, SEEK_SET);

    char current_line[16];
    int i = 0;
    while (fgets(current_line, 16, fptr) != NULL)
    {
        char *token = strtok(current_line, " ");
        int as_number = atoi(token);
        col1[i] = as_number;
        token = strtok(NULL, " ");
        int as_number2 = atoi(token);
        col2[i] = as_number2;
        i++;
    }

    int similarity_score = 0;
    for (int i = 0; i < total_lines; i++)
    {
        int current_in_first = col1[i];
        for (int j = 0; j < total_lines; j++)
        {
            if (col2[j] == current_in_first)
            {
                similarity_score += current_in_first;
            }
        }
    }

    printf("Similarity score: %d\n", similarity_score);

    fclose(fptr);

    return 0;
}
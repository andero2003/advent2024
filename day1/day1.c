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

    sort(col1, total_lines);
    sort(col2, total_lines);

    int total_distance = 0;
    for (int i = 0; i < total_lines; i++)
    {
        total_distance += abs(col1[i] - col2[i]);
    }

    printf("Total distance: %d\n", total_distance);

    fclose(fptr);

    return 0;
}
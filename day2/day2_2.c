#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sign(int x)
{
    return (x > 0) - (x < 0);
}

int main()
{
    FILE *fptr;
    fptr = fopen("day2.txt", "r");

    int total_lines = 0;
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '\n')
        {
            total_lines++;
        }
    }

    fseek(fptr, 0, SEEK_SET);

    char current_line[30];
    int safe_reports = 0;
    int i = 0;
    while (fgets(current_line, 30, fptr) != NULL)
    {
        char *current_line_copy = strdup(current_line);
        char *t = strtok(current_line, " ");

        int val_count = 0;
        while (t)
        {
            int as_number = atoi(t);
            t = strtok(NULL, " ");
            val_count++;
        }

        int *values = (int *)malloc(val_count * sizeof(int));

        char *new_token = strtok(current_line_copy, " ");
        int j = 0;
        while (new_token)
        {
            int as_number = atoi(new_token);
            values[j] = as_number;
            new_token = strtok(NULL, " ");
            j++;
        }

        // Check if any safe when removing one value
        int any_safe = 0;

        for (int index_to_ignore = 0; index_to_ignore < val_count; index_to_ignore++)
        {
            printf("\n");
            int *new_values = (int *)malloc((val_count - 1) * sizeof(int));
            int new_values_index = 0;
            for (int k = 0; k < val_count; k++)
            {
                if (k == index_to_ignore)
                {
                    continue;
                }
                new_values[new_values_index] = values[k];
                new_values_index++;
            }

            for (int k = 0; k < val_count - 1; k++)
            {
                printf("%d ", new_values[k]);
            }
            printf("\n");

            int is_safe = 1;

            int last_number = -1;
            int last_diff = 0;

            for (int k = 0; k < val_count - 1; k++)
            {
                if (last_number == -1)
                {
                    last_number = new_values[k];
                    continue;
                }

                int diff = new_values[k] - last_number;
                last_number = new_values[k];

                if (abs(diff) < 1 || abs(diff) > 3)
                {
                    is_safe = 0;
                    break;
                }

                if (last_diff != 0 && sign(diff) != sign(last_diff))
                {
                    is_safe = 0;
                    break;
                }
                last_diff = diff;
            }

            if (is_safe)
            {
                printf("Safe\n");
                any_safe = 1;
                break;
            }
        }

        safe_reports += any_safe;
        i++;
    }

    printf("Safe reports: %d\n", safe_reports);

    return 0;
}
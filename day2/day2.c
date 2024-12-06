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
        // if (i < 10)
        // {
        //     i++;
        //     continue;
        // }

        char *token = strtok(current_line, " ");

        int last_number = -1;
        int last_diff = 0;

        int is_safe = 1;

        printf("Line %d\n", i);

        while (token)
        {
            int as_number = atoi(token);
            if (last_number != -1)
            {
                int diff = as_number - last_number;
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

            last_number = as_number;
            token = strtok(NULL, " ");
        }

        safe_reports += is_safe;

        i++;
        // break;
    }

    printf("Safe reports: %d\n", safe_reports);

    return 0;
}
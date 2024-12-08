#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line_count(FILE *fptr)
{
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

    return total_lines;
}

int dp(long long target, int *numbers, int count)
{
    if (count == 1 && numbers[0] == target)
        return 1; // base case
    if (count == 1 && numbers[0] != target)
        return 0; // base case

    int last_number = numbers[count - 1];
    int *new_numbers = (int *)malloc((count - 1) * sizeof(int));
    for (int i = 0; i < count - 1; i++)
    {
        new_numbers[i] = numbers[i];
    }
    // addition and multiplication
    int ways = 0;
    ways += dp(target - last_number, new_numbers, count - 1);
    if (target % last_number == 0)
        ways += dp(target / last_number, new_numbers, count - 1);

    return ways;
}

int main()
{
    FILE *fptr;
    fptr = fopen("day7.txt", "r");

    long long total = 0;

    // parse all lines
    char line[100];
    while (fgets(line, sizeof(line), fptr))
    {
        // split at colon
        char *token = strtok(line, ":");
        char *key = token;
        char *value = strtok(NULL, ":");

        long long needed_result = atoll(key);

        // parse the remaining numbers separated by space
        int *numbers = (int *)malloc(20 * sizeof(int)); // 20 should be enough
        int count = 0;
        char *tok2 = strtok(value, " ");
        while (tok2 != NULL)
        {
            numbers[count] = atoi(tok2);
            count++;
            tok2 = strtok(NULL, " ");
        }

        int res = dp(needed_result, numbers, count);
        if (res > 0)
        {
            printf("\n");
            total += needed_result;
        }
    }

    printf("Total: %lld\n", total);

    fclose(fptr);

    return 0;
}
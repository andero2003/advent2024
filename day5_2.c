#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int before;
    int after;
} Rule;

typedef struct
{
    int nodes[25];
    int edges[25][25];
    int node_count;
    int edge_count;
} Graph;

//

int main()
{
    FILE *fptr;
    fptr = fopen("day5.txt", "r");

    int total = 0;
    int RULE_COUNT = 1176;

    Rule rules[RULE_COUNT];

    char current_line[10];
    int i = 0;
    while (fgets(current_line, 10, fptr) != NULL)
    {
        int before, after;
        if (sscanf(current_line, "%d|%d", &before, &after) == 2)
        {
            printf("Before: %d, After: %d\n", before, after);
            rules[i].before = before;
            rules[i].after = after;
        }

        i++;
        if (i == RULE_COUNT)
        {
            break;
        }
    }
    // empty line
    fgets(current_line, 5, fptr);
    // sequences
    i = 0;

    char sequence_line[100];

    while (fgets(sequence_line, 100, fptr) != NULL)
    {
        printf("Sequence: %s\n", sequence_line);
        int seq_len = (strlen(sequence_line) + 1) / 3; // 2 digit numbers, separated by commas

        int sequence[seq_len];
        int index_map[100];
        for (int j = 0; j < 100; j++)
        {
            index_map[j] = -1;
        }

        char *token = strtok(sequence_line, ",");
        int j = 0;
        while (token != NULL)
        {
            int num;
            if (sscanf(token, "%d", &num) == 1)
            {
                sequence[j] = num;
                index_map[num] = j;
            }
            token = strtok(NULL, ",");
            j++;
        }

        // verify rules
        int valid = 1;
        for (int j = 0; j < RULE_COUNT; j++)
        {
            Rule rule = rules[j];
            if (index_map[rule.before] == -1 || index_map[rule.after] == -1)
                continue;
            if (index_map[rule.before] >= index_map[rule.after])
            {
                valid = 0;
                break;
            }
        }
        if (valid == 0)
        {
            printf("Sequence is invalid\n");
            for (int j = 0; j < seq_len; j++)
            {
                printf("%d ", sequence[j]);
            }
            while (valid == 0)
            {
                // swap any breaking rules
                for (int j = 0; j < RULE_COUNT; j++)
                {
                    Rule rule = rules[j];

                    if (index_map[rule.before] == -1 || index_map[rule.after] == -1)
                    {
                        // Ignore rules that don't apply
                        continue;
                    }

                    if (index_map[rule.before] >= index_map[rule.after])
                    {
                        int temp = sequence[index_map[rule.before]];
                        sequence[index_map[rule.before]] = sequence[index_map[rule.after]];
                        sequence[index_map[rule.after]] = temp;

                        int temp_index = index_map[rule.before];
                        index_map[rule.before] = index_map[rule.after];
                        index_map[rule.after] = temp_index;

                        printf("Swapped %d and %d\n", rule.before, rule.after);
                        break;
                    }
                }

                // verify rules
                valid = 1;
                for (int j = 0; j < RULE_COUNT; j++)
                {
                    Rule rule = rules[j];
                    if (index_map[rule.before] == -1 || index_map[rule.after] == -1)
                        continue;
                    if (index_map[rule.before] >= index_map[rule.after])
                    {
                        printf("Violated rule %d\n", j);
                        valid = 0;
                        break;
                    }
                }
            }

            // at this point, the sequence is valid ??
            int middle_index = (seq_len - 1) / 2;
            int middle = sequence[middle_index];
            total += middle;
        }

        i++;
    }

    printf("Total: %d\n", total);

    return 0;
}
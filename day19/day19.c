#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATTERNS 750
#define MAX_DESIGNS 500
#define MAX_LINE_LENGTH 3000
#define MAX_PATTERN_LENGTH 15

int dp(char *design, char patterns[MAX_PATTERNS][MAX_PATTERN_LENGTH], int pattern_count)
{
    if (strlen(design) == 0)
    {
        return 1; // Found a match
    }

    // Check if any pattern matches the design
    for (int i = 0; i < pattern_count; i++)
    {
        char *pattern = patterns[i];
        if (strcmp(design, pattern) == 0)
        {
            return 1; // Found a match
        }
    }

    // Check for substring at the beginning and repeat
    int any_possible = 0;
    for (int i = 0; i < pattern_count; i++)
    {
        char *pattern = patterns[i];
        int pattern_length = strlen(pattern);

        // Skip if pattern is longer than design
        if (pattern_length > strlen(design))
        {
            continue;
        }

        if (strncmp(design, pattern, pattern_length) == 0)
        {
            printf("recurse %s %s\n", design + pattern_length, pattern);
            any_possible += dp(design + pattern_length, patterns, pattern_count);
        }
    }

    return any_possible;
}

int main()
{
    FILE *file = fopen("day19.txt", "r");
    if (!file)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }

    char patterns[MAX_PATTERNS][MAX_PATTERN_LENGTH];
    char designs[MAX_DESIGNS][MAX_LINE_LENGTH];
    int pattern_count = 0, design_count = 0;

    // Read first line for patterns
    char line[MAX_LINE_LENGTH];
    if (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ", \n");
        while (token && pattern_count < MAX_PATTERNS)
        {
            strncpy(patterns[pattern_count++], token, MAX_PATTERN_LENGTH);
            printf("pattern: %s\n", token);
            token = strtok(NULL, ", \n");
        }
    }

    // Read remaining lines for designs
    while (fgets(line, sizeof(line), file) && design_count < MAX_DESIGNS)
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        if (strlen(line) > 0)
        {
            strncpy(designs[design_count++], line, MAX_LINE_LENGTH);
        }
    }

    fclose(file);

    int possible_designs = 0;
    for (int i = 0; i < design_count; i++)
    {
        char *design = designs[i];
        possible_designs += dp(design, patterns, pattern_count);
    }

    printf("Possible designs: %d\n", possible_designs);

    return 0;
}
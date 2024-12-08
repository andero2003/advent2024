#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_grid_dimensions(FILE *fptr, int *rows, int *cols)
{
    char ch;
    int total_cols = 0;
    int total_rows = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '\n')
        {
            total_rows++;
        }
        else
        {
            total_cols++;
        }
    }

    *rows = total_rows;
    *cols = total_cols / total_rows;
}

int main()
{
    FILE *fptr;
    fptr = fopen("day8.txt", "r");

    int total_rows = 50, total_cols = 50;
    // get_grid_dimensions(fptr, &total_rows, &total_cols);
    fseek(fptr, 0, SEEK_SET);

    char grid[total_rows][total_cols];
    char antinodes[total_rows][total_cols];
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            antinodes[i][j] = '.';
        }
    }

    char ch;
    int row = 0;
    int col = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '\n')
        {
            row++;
            col = 0;
        }
        else
        {
            grid[row][col] = ch;
            col++;
        }
    }

    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            char frequency = grid[i][j];
            if (frequency != '.')
            {
                for (int i2 = 0; i2 < total_rows; i2++)
                {
                    for (int j2 = 0; j2 < total_cols; j2++)
                    {
                        char frequency2 = grid[i2][j2];
                        if (frequency2 == frequency && i != i2 && j != j2)
                        {
                            int diff_i = i - i2;
                            int diff_j = j - j2;

                            int antinode1_i = i + diff_i;
                            int antinode1_j = j + diff_j;

                            int antinode2_i = i2 - diff_i;
                            int antinode2_j = j2 - diff_j;

                            if (antinode1_i >= 0 && antinode1_i < total_rows && antinode1_j >= 0 && antinode1_j < total_cols)
                            {
                                antinodes[antinode1_i][antinode1_j] = '#';
                            }
                        }
                    }
                }
            }
        }
    }

    int total_antinodes = 0;
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            if (antinodes[i][j] == '#')
            {
                total_antinodes++;
            }
        }
    }

    printf("Total antinodes: %d\n", total_antinodes);

    fclose(fptr);

    return 0;
}
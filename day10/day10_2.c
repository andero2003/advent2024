#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(int *grid, int i, int j, int total_rows, int total_cols, int *reachable_ends)
{
    int current_height = *(grid + i * total_cols + j);
    if (current_height == 9)
    {
        *(reachable_ends + i * total_cols + j) += 1;
        return 0; // reached the end of the trail
    }

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (di == 0 && dj == 0)
                continue;
            if (di != 0 && dj != 0)
                continue;

            int new_i = i + di;
            int new_j = j + dj;
            if (new_i >= 0 && new_i < total_rows && new_j >= 0 && new_j < total_cols)
            {
                int new_height = *(grid + new_i * total_cols + new_j);
                if (new_height == current_height + 1)
                {
                    search(grid, new_i, new_j, total_rows, total_cols, reachable_ends);
                }
            }
        }
    }
    return 0;
}

int main()
{
    FILE *fptr;
    fptr = fopen("day10.txt", "r");

    int total_rows = 40, total_columns = 40;

    int grid[total_rows][total_columns];

    char ch;
    int row = 0, column = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '\n')
        {
            row++;
            column = 0;
        }
        else
        {
            grid[row][column] = ch - '0';
            column++;
        }
    }

    int scores = 0;
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_columns; j++)
        {
            if (grid[i][j] != 0)
                continue; // not a trailhead
            int reachable_ends[total_rows][total_columns];
            for (int k = 0; k < total_rows; k++)
            {
                for (int l = 0; l < total_columns; l++)
                {
                    reachable_ends[k][l] = 0;
                }
            }
            search((int *)grid, i, j, total_rows, total_columns, (int *)reachable_ends);
            // sum up scores todo

            for (int k = 0; k < total_rows; k++)
            {
                for (int l = 0; l < total_columns; l++)
                {
                    printf("%d ", reachable_ends[k][l]);
                    if (reachable_ends[k][l] > 0)
                    {
                        scores += reachable_ends[k][l];
                    }
                }
                printf("\n");
            }

            printf("\n");
        }
    }

    printf("Scores: %d\n", scores);

    fclose(fptr);

    return 0;
}
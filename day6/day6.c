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

int is_in_bounds(int row, int col, int total_rows, int total_cols)
{
    return row >= 0 && row < total_rows && col >= 0 && col < total_cols;
}

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

void turn_right(enum Direction *current_direction)
{
    switch (*current_direction)
    {
    case UP:
        *current_direction = RIGHT;
        break;
    case RIGHT:
        *current_direction = DOWN;
        break;
    case DOWN:
        *current_direction = LEFT;
        break;
    case LEFT:
        *current_direction = UP;
        break;
    default:
        break;
    }
}

void get_dx_dy_for_direction(int *dx, int *dy, enum Direction current_direction)
{
    switch (current_direction)
    {
    case UP:
        *dx = -1;
        *dy = 0;
        break;
    case RIGHT:
        *dx = 0;
        *dy = 1;
        break;
    case DOWN:
        *dx = 1;
        *dy = 0;
        break;
    case LEFT:
        *dx = 0;
        *dy = -1;
        break;
    default:
        break;
    }
}

int main()
{
    FILE *fptr;
    fptr = fopen("day6.txt", "r");

    int total_rows, total_cols;
    get_grid_dimensions(fptr, &total_rows, &total_cols);

    printf("Rows: %d, Cols: %d\n", total_rows, total_cols);

    fseek(fptr, 0, SEEK_SET);

    char grid[total_rows][total_cols];
    char ch;
    int row = 0;
    int col = 0;

    int current_row = 0;
    int current_col = 0;
    enum Direction current_direction = UP; // default direction

    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == '\n')
        {
            row++;
            col = 0;
        }
        else
        {
            if (ch == '^')
            {
                current_col = col;
                current_row = row;
            }
            grid[row][col] = ch;
            col++;
        }
    }

    int distinct_cell_count = 0;

    while (is_in_bounds(current_row, current_col, total_rows, total_cols))
    {
        int dx, dy;
        get_dx_dy_for_direction(&dx, &dy, current_direction);

        char current_cell = grid[current_row][current_col];
        if (current_cell == '.')
        {
            distinct_cell_count++;
        }
        grid[current_row][current_col] = 'X';

        int lookahead_row = current_row + dx;
        int lookahead_col = current_col + dy;

        if (!is_in_bounds(lookahead_row, lookahead_col, total_rows, total_cols))
            break; // exited the mapped area

        if (grid[lookahead_row][lookahead_col] == '#')
        {
            turn_right(&current_direction);
        }
        else
        {
            current_row = lookahead_row;
            current_col = lookahead_col;
        }

        printf("Santa is at: (%d, %d)\n", current_row, current_col);
    }

    // print final grid
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    printf("Distinct cell count: %d\n", distinct_cell_count);

    fclose(fptr);

    return 0;
}
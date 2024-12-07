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

    int total_rows = 130;
    int total_cols = 130;
    // get_grid_dimensions(fptr, &total_rows, &total_cols);

    printf("Rows: %d, Cols: %d\n", total_rows, total_cols);

    fseek(fptr, 0, SEEK_SET);

    char grid[total_rows][total_cols];
    char ch;
    int row = 0;
    int col = 0;

    int start_row = 0;
    int start_col = 0;

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
                start_row = row;
                start_col = col;
            }
            grid[row][col] = ch;
            col++;
        }
    }

    int valid_obstacle_combinations = 0;
    for (int obstacle_row = 0; obstacle_row < total_rows; obstacle_row++)
    {
        for (int obstacle_col = 0; obstacle_col < total_cols; obstacle_col++)
        {
            // if already obstacle or start position, skip
            if (grid[obstacle_row][obstacle_col] == '#' || (obstacle_row == start_row && obstacle_col == start_col))
                continue;

            grid[obstacle_row][obstacle_col] = '#';

            int current_row = start_row;
            int current_col = start_col;
            enum Direction current_direction = UP; // default direction

            int visit_count[total_rows][total_cols];
            for (int i = 0; i < total_rows; i++)
            {
                for (int j = 0; j < total_cols; j++)
                {
                    visit_count[i][j] = 0;
                }
            }

            while (is_in_bounds(current_row, current_col, total_rows, total_cols))
            {
                int dx, dy;
                get_dx_dy_for_direction(&dx, &dy, current_direction);

                if (visit_count[current_row][current_col] > 20) // lmfao they HAVE to be in a loop now right ??
                {
                    valid_obstacle_combinations++;
                    break; // loop detected
                }

                visit_count[current_row][current_col]++;
                if (current_row != start_row || current_col != start_col)
                {
                    grid[current_row][current_col] = 'X';
                }

                // detect loop

                int lookahead_row = current_row + dx;
                int lookahead_col = current_col + dy;

                if (!is_in_bounds(lookahead_row, lookahead_col, total_rows, total_cols))
                    break; // exited the mapped area

                while (grid[lookahead_row][lookahead_col] == '#')
                {
                    turn_right(&current_direction);
                    get_dx_dy_for_direction(&dx, &dy, current_direction);
                    lookahead_row = current_row + dx;
                    lookahead_col = current_col + dy;
                }
                current_row = lookahead_row;
                current_col = lookahead_col;
            }

            // reset grid
            for (int i = 0; i < total_rows; i++)
            {
                for (int j = 0; j < total_cols; j++)
                {
                    if (grid[i][j] == 'X' || grid[i][j] == 'Y')
                    {
                        grid[i][j] = '.';
                    }
                }
            }
            grid[obstacle_row][obstacle_col] = '.';
        }
    }

    printf("Valid obstacle combinations: %d\n", valid_obstacle_combinations);

    fclose(fptr);

    return 0;
}
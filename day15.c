#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void apply_movement(char movement, int *row, int *col)
{
    switch (movement)
    {
    case '^':
        (*row)--;
        break;
    case 'v':
        (*row)++;
        break;
    case '<':
        (*col)--;
        break;
    case '>':
        (*col)++;
        break;
    default:
        break;
    }
}

int main()
{
    FILE *fptr;
    fptr = fopen("day15.txt", "r");

    int total_rows = 50, total_cols = 50;

    // read grid
    char grid[total_rows][total_cols];
    char ch;
    int row = 0, column = 0;

    int robot_row, robot_col;

    while ((ch = fgetc(fptr)) != EOF)
    {
        if (row >= total_rows)
        {
            break;
        }
        if (ch == '\n')
        {
            row++;
            column = 0;
        }
        else
        {
            if (ch == '@') // robot
            {
                // grid[row][column] = '.';
                robot_row = row;
                robot_col = column;
            }
            grid[row][column] = ch;

            column++;
        }
    }

    int move_count = 20038;
    // read moves
    char moves[move_count];
    int i = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (i >= move_count)
        {
            break;
        }
        if (ch == '\n')
        {
            continue;
        }
        moves[i] = ch;
        i++;
    }

    for (int i = 0; i < move_count; i++)
    {

        // printf("Grid:\n");
        // for (int i = 0; i < total_rows; i++)
        // {
        //     for (int j = 0; j < total_cols; j++)
        //     {
        //         printf("%c", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        char move = moves[i];
        int new_row = robot_row, new_col = robot_col;
        apply_movement(move, &new_row, &new_col);
        // printf("Trying to move to: %d, %d\n", new_row, new_col);
        // printf("Cell: %c\n", grid[new_row][new_col]);

        char new_cell = grid[new_row][new_col];
        if (new_cell == '.')
        {
            // empty cell, move robot
            grid[new_row][new_col] = '@';
            grid[robot_row][robot_col] = '.';
            robot_row = new_row;
            robot_col = new_col;
            continue;
        }

        // Otherwise, check if there is an empty space in the direction of the move, regardless of how many boxes the robot has to move
        int new_row2 = new_row, new_col2 = new_col;
        char new_cell2 = grid[new_row2][new_col2];
        while (new_cell2 == 'O') // box
        {
            apply_movement(move, &new_row2, &new_col2);
            new_cell2 = grid[new_row2][new_col2];
        }
        if (new_cell2 == '#')
        {
            // printf("Wall\n");
            continue; // wall
        }

        // Move all boxes in the direction of the move and robot
        int new_row3 = new_row, new_col3 = new_col;
        char new_cell3 = grid[new_row3][new_col3];
        while (new_cell3 == 'O') // box
        {
            apply_movement(move, &new_row3, &new_col3);
            new_cell3 = grid[new_row3][new_col3];
        }
        grid[new_row3][new_col3] = 'O';
        // move robot
        grid[new_row][new_col] = '@';
        grid[robot_row][robot_col] = '.';

        robot_row = new_row;
        robot_col = new_col;
    }

    int gps_sum = 0;
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            if (grid[i][j] == 'O')
            {
                gps_sum += 100 * i + j;
            }
        }
    }
    printf("GPS sum: %d\n", gps_sum);

    return 0;
}
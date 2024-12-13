#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Region
{
    int *x_coords;
    int *y_coords;
    int num_coords;
};

void dynamically_add_coords(struct Region *region, int x, int y)
{
    region->num_coords++;
    int *new_x_coords = (int *)malloc(region->num_coords * sizeof(int));
    int *new_y_coords = (int *)malloc(region->num_coords * sizeof(int));

    for (int i = 0; i < region->num_coords - 1; i++)
    {
        new_x_coords[i] = region->x_coords[i];
        new_y_coords[i] = region->y_coords[i];
    }
    new_x_coords[region->num_coords - 1] = x;
    new_y_coords[region->num_coords - 1] = y;

    free(region->x_coords);
    free(region->y_coords);

    region->x_coords = new_x_coords;
    region->y_coords = new_y_coords;
}

void search_from(struct Region *region, char *grid, int i, int j, int total_rows, int total_columns)
{
    char current_region = *(grid + i * total_rows + j);
    if (current_region == '_')
        return; // mark visited regions

    dynamically_add_coords(region, i, j);
    *(grid + i * total_rows + j) = '_'; // mark visited

    // seach all 4 directions
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
            if (new_i >= 0 && new_i < total_rows && new_j >= 0 && new_j < total_columns)
            {
                if (*(grid + new_i * total_rows + new_j) == current_region)
                {
                    search_from(region, grid, new_i, new_j, total_rows, total_columns);
                }
            }
        }
    }
}

int bounds_something_else(char *grid, int i, int j, int total_rows, int total_columns)
{
    char current_region = *(grid + i * total_rows + j);
    int perimeter = 0;
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
            if (new_i >= 0 && new_i < total_rows && new_j >= 0 && new_j < total_columns)
            {
                if (*(grid + new_i * total_rows + new_j) != current_region)
                {
                    perimeter++;
                }
            }
            else
            {
                perimeter++;
            }
        }
    }
    return perimeter;
};

int get_max(int *arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int get_min(int *arr, int n)
{
    int min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int main()
{
    FILE *fptr;
    fptr = fopen("day12.txt", "r");

    int total_rows = 10, total_columns = 10;
    char grid[total_rows][total_columns];

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
            grid[row][column] = ch;
            column++;
        }
    }

    char mutated_grid[total_rows][total_columns];
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_columns; j++)
        {
            mutated_grid[i][j] = grid[i][j];
        }
    }

    int total_price = 0;
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_columns; j++)
        {
            char current_region = mutated_grid[i][j];
            if (current_region == '_')
                continue; // mark visited regions

            struct Region region = (struct Region){0};
            search_from(&region, &mutated_grid, i, j, total_rows, total_columns);

            printf("Region %c: ", current_region);
            printf("Min x: %d, Max x: %d, Min y: %d, Max y: %d\n", get_min(region.x_coords, region.num_coords), get_max(region.x_coords, region.num_coords), get_min(region.y_coords, region.num_coords), get_max(region.y_coords, region.num_coords));
            // for (int k = 0; k < region.num_coords; k++)
            // {
            //     printf("(%d, %d) ", region.x_coords[k], region.y_coords[k]);
            // }
            printf("\n");

            int area = region.num_coords;
            int sides = 0;

            total_price += area * sides;
        }
    }

    printf("\n");
    printf("Total price: %d\n", total_price);

    fclose(fptr);

    return 0;
}
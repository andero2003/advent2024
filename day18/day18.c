#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3

struct Node
{
    int row;
    int col;
    int direction;
    int score;
    struct Node *next;
};

struct Queue
{
    struct Node *head;
    struct Node *tail;
    int size;
};

//

void enqueue(struct Queue *queue, int row, int col, int direction, int score)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->row = row;
    node->col = col;
    node->direction = direction;
    node->score = score;
    node->next = NULL;

    if (queue->size == 0)
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
}

// dequeue node with LOWEST score eg some bullshit heap
void dequeue(struct Queue *queue, struct Node *node)
{
    if (queue->size == 0)
    {
        return;
    }

    struct Node *current = queue->head;
    struct Node *prev = NULL;

    struct Node *min_node = current;
    struct Node *min_prev = NULL;

    while (current != NULL)
    {
        if (current->score < min_node->score)
        {
            min_node = current;
            min_prev = prev;
        }
        prev = current;
        current = current->next;
    }

    if (min_prev == NULL)
    {
        queue->head = min_node->next;
    }
    else
    {
        min_prev->next = min_node->next;
    }

    if (min_node == queue->tail)
    {
        queue->tail = min_prev;
    }

    *node = *min_node;
    queue->size--;
}

void apply_movement(int direction, int *row, int *col)
{
    switch (direction)
    {
    case EAST:
        *col += 1;
        break;
    case SOUTH:
        *row += 1;
        break;
    case WEST:
        *col -= 1;
        break;
    case NORTH:
        *row -= 1;
        break;
    }
}

int main()
{

    FILE *fptr;
    fptr = fopen("day18.txt", "r");

    int total_rows = 73, total_cols = 73;

    // read grid
    char grid[total_rows][total_cols];
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            grid[i][j] = '.';
            if (i == 0 || i == total_rows - 1 || j == 0 || j == total_cols - 1)
            {
                grid[i][j] = '#';
            }
        }
    }

    int row, col;
    int i = 0;
    while (fscanf(fptr, "%d,%d\n", &col, &row) == 2)
    {
        printf("line %d\n", i);
        i++;

        grid[1 + row][1 + col] = '#';
        int start_row = 1, start_col = 1;
        int end_row = total_cols - 2, end_col = total_cols - 2;

        // clear all visited
        for (int i = 0; i < total_rows; i++)
        {
            for (int j = 0; j < total_cols; j++)
            {
                if (grid[i][j] == 'V')
                {
                    grid[i][j] = '.';
                }
            }
        }

        int current_row = start_row, current_col = start_col;
        int current_direction = EAST;

        struct Queue queue;
        queue.size = 0;
        enqueue(&queue, current_row, current_col, current_direction, 0);

        int local_solution_found = 0;

        while (queue.size > 0)
        {
            // bfs
            struct Node node;
            dequeue(&queue, &node);

            current_row = node.row;
            current_col = node.col;
            current_direction = node.direction;
            int current_score = node.score;

            // bounds check
            if (current_row < 0 || current_row >= total_rows || current_col < 0 || current_col >= total_cols)
            {
                continue;
            }

            // forward
            int forward_row = current_row, forward_col = current_col;
            apply_movement(current_direction, &forward_row, &forward_col);
            if (grid[forward_row][forward_col] != '#' && grid[forward_row][forward_col] != 'V')
            {
                if (forward_row == end_row && forward_col == end_col)
                {
                    local_solution_found = 1;
                    break;
                }
                grid[forward_row][forward_col] = 'V'; // mark as visited
                enqueue(&queue, forward_row, forward_col, current_direction, current_score + 1);
            }

            // left
            int left_row = current_row, left_col = current_col;
            int left_direction = (current_direction + 3) % 4;
            apply_movement(left_direction, &left_row, &left_col);
            if (grid[left_row][left_col] != '#' && grid[left_row][left_col] != 'V')
            {
                if (left_row == end_row && left_col == end_col)
                {
                    local_solution_found = 1;
                    break;
                }

                grid[left_row][left_col] = 'V'; // mark as visited
                enqueue(&queue, left_row, left_col, left_direction, current_score + 1);
            }

            // right
            int right_row = current_row, right_col = current_col;
            int right_direction = (current_direction + 1) % 4;
            apply_movement(right_direction, &right_row, &right_col);
            if (grid[right_row][right_col] != '#' && grid[right_row][right_col] != 'V')
            {
                if (right_row == end_row && right_col == end_col)
                {
                    local_solution_found = 1;
                    break;
                }
                grid[right_row][right_col] = 'V'; // mark as visited
                enqueue(&queue, right_row, right_col, right_direction, current_score + 1);
            }

            // down
            int down_row = current_row, down_col = current_col;
            int down_direction = (current_direction + 2) % 4;
            apply_movement(down_direction, &down_row, &down_col);
            if (grid[down_row][down_col] != '#' && grid[down_row][down_col] != 'V')
            {
                if (down_row == end_row && down_col == end_col)
                {
                    printf("found end\n");
                    printf("score %d\n", current_score + 1);
                    break;
                }
                grid[down_row][down_col] = 'V'; // mark as visited
                enqueue(&queue, down_row, down_col, down_direction, current_score + 1);
            }
        }
        if (local_solution_found == 0)
        {
            printf("no solution at %d %d\n", row, col);
            break;
        }
    }

    printf("grid\n");
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    printf("done\n");

    fclose(fptr);

    return 0;
}
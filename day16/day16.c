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
    fptr = fopen("day16.txt", "r");

    int total_rows = 141, total_cols = 141;

    // read grid
    char grid[total_rows][total_cols];
    char ch;
    int row = 0, column = 0;

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
            grid[row][column] = ch;
            column++;
        }
    }

    int start_row = total_rows - 2, start_col = 1;
    int end_row = 1, end_col = total_cols - 2;

    int current_row = start_row, current_col = start_col;
    int current_direction = EAST;

    struct Queue queue;
    queue.size = 0;
    enqueue(&queue, current_row, current_col, current_direction, 0);

    while (queue.size > 0)
    {
        // bfs
        struct Node node;
        dequeue(&queue, &node);
        printf("exploring %d %d\n", node.row, node.col);

        current_row = node.row;
        current_col = node.col;
        current_direction = node.direction;
        int current_score = node.score;

        // consider forward, left, right

        // forward
        int forward_row = current_row, forward_col = current_col;
        apply_movement(current_direction, &forward_row, &forward_col);
        if (grid[forward_row][forward_col] != '#' && grid[forward_row][forward_col] != 'V')
        {
            if (forward_row == end_row && forward_col == end_col)
            {
                printf("found end\n");
                printf("score %d\n", current_score + 1);
                break;
            }
            printf("adding forward %d %d\n", forward_row, forward_col);
            grid[forward_row][forward_col] = 'V'; // mark as visited
            enqueue(&queue, forward_row, forward_col, current_direction, current_score + 1);
        }

        // left
        int left_row = current_row, left_col = current_col;
        int left_direction = (current_direction + 3) % 4;
        apply_movement(left_direction, &left_row, &left_col);
        if (grid[left_row][left_col] != '#' && grid[left_row][left_col] != 'V')
        {
            printf("adding left %d %d\n", left_row, left_col);
            if (left_row == end_row && left_col == end_col)
            {
                printf("found end\n");
                printf("score %d\n", current_score + 1001);
                break;
            }

            grid[left_row][left_col] = 'V'; // mark as visited
            enqueue(&queue, left_row, left_col, left_direction, current_score + 1001);
        }

        // right
        int right_row = current_row, right_col = current_col;
        int right_direction = (current_direction + 1) % 4;
        apply_movement(right_direction, &right_row, &right_col);
        if (grid[right_row][right_col] != '#' && grid[right_row][right_col] != 'V')
        {
            if (right_row == end_row && right_col == end_col)
            {
                printf("found end\n");
                printf("score %d\n", current_score + 1001);
                break;
            }
            printf("adding right %d %d\n", right_row, right_col);
            grid[right_row][right_col] = 'V'; // mark as visited
            enqueue(&queue, right_row, right_col, right_direction, current_score + 1001);
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
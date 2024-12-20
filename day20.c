#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TOTAL_ROWS 141
#define TOTAL_COLUMNS 141

struct Node
{
    int row;
    int column;
    int score;
    struct Node *next;
};

struct Queue
{
    struct Node *head;
    struct Node *tail;
    int size;
};

void enqueue(struct Queue *queue, int row, int column, int score)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->row = row;
    node->column = column;
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

int bfs(char grid[TOTAL_ROWS][TOTAL_COLUMNS], int start_row, int start_column, int end_row, int end_column)
{
    // clear visited
    for (int i = 0; i < TOTAL_ROWS; i++)
    {
        for (int j = 0; j < TOTAL_COLUMNS; j++)
        {
            if (grid[i][j] == 'V')
            {
                grid[i][j] = '.'; // reset
            }
        }
    }

    struct Queue queue;
    queue.size = 0;
    enqueue(&queue, start_row, start_column, 0);
    while (queue.size > 0)
    {
        struct Node node;
        dequeue(&queue, &node);
        int current_row = node.row;
        int current_column = node.column;
        int current_score = node.score;

        if (current_row < 0 || current_row >= TOTAL_ROWS || current_column < 0 || current_column >= TOTAL_COLUMNS)
        {
            continue;
        }

        if (grid[current_row][current_column] == '#' || grid[current_row][current_column] == 'V')
        {
            continue;
        }

        if (current_row == end_row && current_column == end_column)
        {
            return current_score;
        }

        grid[current_row][current_column] = 'V'; // visited

        enqueue(&queue, current_row + 1, current_column, current_score + 1);
        enqueue(&queue, current_row - 1, current_column, current_score + 1);
        enqueue(&queue, current_row, current_column + 1, current_score + 1);
        enqueue(&queue, current_row, current_column - 1, current_score + 1);
    }
}

//

int main()
{
    FILE *file = fopen("day20.txt", "r");
    if (!file)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int start_row, start_column;
    int end_row, end_column;

    char grid[TOTAL_ROWS][TOTAL_COLUMNS];
    char ch;
    int row = 0, column = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            row++;
            column = 0;
        }
        else
        {
            grid[row][column] = ch;
            if (ch == 'S')
            {
                start_row = row;
                start_column = column;
                grid[row][column] = '.';
            }
            if (ch == 'E')
            {
                end_row = row;
                end_column = column;
                grid[row][column] = '.';
            }

            column++;
        }
    }

    int total_time = bfs(grid, start_row, start_column, end_row, end_column);

    int good_cheats = 0;

    for (int i = 1; i < TOTAL_ROWS - 1; i++) // ignore padding
    {
        for (int j = 1; j < TOTAL_COLUMNS - 1; j++)
        {
            if (grid[i][j] != '#')
                continue; // only consider walls to cheat
            printf("progress %d %d\n", i, j);

            grid[i][j] = '.'; // remove wall
            int new_total_time = bfs(grid, start_row, start_column, end_row, end_column);
            int saving = total_time - new_total_time;
            if (saving >= 100)
            {
                good_cheats++;
            }
            grid[i][j] = '#'; // reset wall
        }
    }

    printf("Good cheats: %d\n", good_cheats);

    fclose(file);

    return 0;
}
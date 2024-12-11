#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct LLNode
{
    unsigned long long value;
    struct LLNode *next;
};

int get_num_length(unsigned long long num)
{
    int length = 0;
    while (num != 0)
    {
        num /= 10;
        length++;
    }
    return length;
}

void split_number(unsigned long long num, unsigned long long *first_half, unsigned long long *second_half)
{
    int length = get_num_length(num);
    int half = length / 2;
    *first_half = num / (unsigned long long)(pow(10, half));
    *second_half = num % (unsigned long long)(pow(10, half));
}

void blink(struct LLNode *head)
{
    struct LLNode *current = head;
    while (current != NULL)
    {
        struct LLNode *next = current->next;
        if (current->value == 0)
        {
            current->value = 1;
        }
        else if (get_num_length(current->value) % 2 == 0)
        {
            // split and create new node
            struct LLNode *new_node = (struct LLNode *)malloc(sizeof(struct LLNode));
            unsigned long long first_half, second_half;

            split_number(current->value, &first_half, &second_half);
            // printf("Splitting %llu into %llu and %llu\n", current->value, first_half, second_half);

            current->value = first_half;
            new_node->value = second_half;
            new_node->next = current->next;
            current->next = new_node;
        }
        else
        {
            current->value = current->value * 2024;
        }
        current = next;
    }
}

void print_linked_list(struct LLNode *head)
{
    struct LLNode *current = head;
    while (current != NULL)
    {
        printf("%llu ", current->value);
        current = current->next;
    }
    printf("\n");
}

struct LLNode *convert_to_linked_list(int *arr, int length)
{
    struct LLNode *head = (struct LLNode *)malloc(sizeof(struct LLNode));
    head->value = arr[0];

    struct LLNode *current = head;
    for (int i = 1; i < length; i++)
    {
        struct LLNode *new_node = (struct LLNode *)malloc(sizeof(struct LLNode));
        new_node->value = arr[i];

        current->next = new_node;
        current = new_node;
    }

    return head;
}

int main()
{
    // initial linked list
    int arr[] = {89749, 6061, 43, 867, 1965860, 0, 206250};
    struct LLNode *head = convert_to_linked_list(arr, 8);

    for (int i = 0; i < 75; i++)
    {
        printf("iteration %d:\n ", i);
        blink(head);
        // print_linked_list(head);
    }

    // count
    int total = 0;
    struct LLNode *current = head;
    while (current != NULL)
    {
        total += 1;
        current = current->next;
    }

    printf("Total: %d\n", total);

    return 0;
}
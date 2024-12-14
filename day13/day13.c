#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_optimal_token_count(int buttonA_X, int buttonA_Y, int buttonB_X, int buttonB_Y, int prize_X, int prize_Y, int tokens)
{
    // printf("Prize: X=%d, Y=%d\n", prize_X, prize_Y);
    // if (prize_X == 0 && prize_Y == 0)
    // {
    //     return tokens; // base case
    // }
    // if (prize_X < 0 || prize_Y < 0)
    // {
    //     return 1000000; // invalid case
    // }

    // Sleep(25);

    // int press_a = get_optimal_token_count(buttonA_X, buttonA_Y, buttonB_X, buttonB_Y, prize_X - buttonA_X, prize_Y - buttonA_Y, tokens + 3);
    // int press_b = get_optimal_token_count(buttonA_X, buttonA_Y, buttonB_X, buttonB_Y, prize_X - buttonB_X, prize_Y - buttonB_Y, tokens + 1);

    // return min(
    //     press_a,
    //     press_b);

    int min_token_price = -1;
    for (int a_presses = 0; a_presses < 100; a_presses++)
    {
        for (int b_presses = 0; b_presses < 100; b_presses++)
        {
            int x = a_presses * buttonA_X + b_presses * buttonB_X;
            int y = a_presses * buttonA_Y + b_presses * buttonB_Y;
            if (x == prize_X && y == prize_Y)
            {
                if (min_token_price == -1 || a_presses * 3 + b_presses < min_token_price)
                {
                    min_token_price = a_presses * 3 + b_presses;
                }
            }
        }
    }

    return min_token_price;
}

int main()
{
    FILE *fptr;
    fptr = fopen("day13.txt", "r");

    int total_token_count = 0;

    int buttonA_X, buttonA_Y, buttonB_X, buttonB_Y, prize_X, prize_Y;
    while (fscanf(fptr, "Button A: X+%d, Y+%d\nButton B: X+%d, Y+%d\nPrize: X=%d, Y=%d\n\n",
                  &buttonA_X, &buttonA_Y, &buttonB_X, &buttonB_Y, &prize_X, &prize_Y) == 6)
    {
        printf("Button A: X+%d, Y+%d\n", buttonA_X, buttonA_Y);
        printf("Button B: X+%d, Y+%d\n", buttonB_X, buttonB_Y);
        printf("Prize: X=%d, Y=%d\n\n", prize_X, prize_Y);

        int token_price = get_optimal_token_count(buttonA_X, buttonA_Y, buttonB_X, buttonB_Y, prize_X, prize_Y, 0);
        if (token_price > 0)
        {
            printf("Optimal token count: %d\n\n", token_price);
            total_token_count += token_price;
        }
    }

    printf("Total token count: %d\n", total_token_count);

    return 0;
}
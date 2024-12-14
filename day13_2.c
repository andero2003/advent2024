#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

size_t max(size_t *arr, int size)
{
    size_t max = arr[0];
    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

double dbl_abs(double x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

size_t round_f(double x)
{
    if (x - (size_t)x >= 0.5)
    {
        return (size_t)x + 1;
    }
    return (size_t)x;
}

size_t get_optimal_token_count(int buttonA_X, int buttonA_Y, int buttonB_X, int buttonB_Y, size_t prize_X, size_t prize_Y)
{
    double ax = (double)buttonA_X;
    double ay = (double)buttonA_Y;
    double bx = (double)buttonB_X;
    double by = (double)buttonB_Y;
    double px = (double)prize_X;
    double py = (double)prize_Y;

    double B_presses = (py - ay * px / ax) / (by - bx * ay / ax);
    double A_presses = (px - B_presses * bx) / ax;
    printf("A presses: %f\n", A_presses);
    printf("B presses: %f\n", B_presses);

    if (dbl_abs(A_presses - round_f(A_presses)) > 0.01 || dbl_abs(B_presses - round_f(B_presses)) > 0.01)
    {
        return 0;
    }

    return round_f(A_presses) * 3 + round_f(B_presses);
}

int main()
{
    FILE *fptr;
    fptr = fopen("day13.txt", "r");

    size_t total_token_count = 0;

    size_t buttonA_X, buttonA_Y, buttonB_X, buttonB_Y, prize_X, prize_Y;
    while (fscanf(fptr, "Button A: X+%llu, Y+%llu\nButton B: X+%llu, Y+%llu\nPrize: X=%llu, Y=%llu\n\n",
                  &buttonA_X, &buttonA_Y, &buttonB_X, &buttonB_Y, &prize_X, &prize_Y) == 6)
    {
        printf("\n");
        printf("Button A: X+%llu, Y+%llu\n", buttonA_X, buttonA_Y);
        printf("Button B: X+%llu, Y+%llu\n", buttonB_X, buttonB_Y);
        printf("Prize: X=%llu, Y=%llu\n", prize_X, prize_Y);
        size_t token_price = get_optimal_token_count(buttonA_X, buttonA_Y, buttonB_X, buttonB_Y, prize_X + 10000000000000, prize_Y + 10000000000000);
        if (token_price > 0)
        {
            printf("Optimal token count: %llu\n\n", token_price);
            total_token_count += token_price;
        }
    }

    printf("Total token count: %llu\n", total_token_count);

    return 0;
}
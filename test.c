#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main()
{
    unsigned long long num = 12345678;
    int half = 4;

    unsigned long long first_half = num / (unsigned long long)(pow(10, half));
    unsigned long long second_half = num % (unsigned long long)(pow(10, half));

    printf("First half: %llu\n", first_half);
    printf("Second half: %llu\n", second_half);
    return 0;
}
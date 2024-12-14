#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fptr;
    fptr = fopen("day14.txt", "r");

    int room_width = 101, room_height = 103;

    for (int SECONDS = 472; SECONDS < 10000; SECONDS += 103)
    {
        fseek(fptr, 0, SEEK_SET);

        int final_positions[room_height][room_width];
        for (int i = 0; i < room_height; i++)
        {
            for (int j = 0; j < room_width; j++)
            {
                final_positions[i][j] = 0;
            }
        }
        printf("Seconds: %d\n", SECONDS);
        int x0, y0, dx, dy;
        while (fscanf(fptr, "p=%d,%d v=%d,%d\n", &x0, &y0, &dx, &dy) == 4)
        {
            // simulate S seconds
            for (int i = 0; i < SECONDS; i++)
            {
                x0 += dx;
                y0 += dy;

                // wrap around
                if (x0 < 0)
                {
                    x0 += room_width;
                }
                if (x0 >= room_width)
                {
                    x0 -= room_width;
                }
                if (y0 < 0)
                {
                    y0 += room_height;
                }
                if (y0 >= room_height)
                {
                    y0 -= room_height;
                }
            }

            final_positions[y0][x0]++;
        }

        printf("Final positions:\n");
        for (int i = 0; i < room_height; i++)
        {
            for (int j = 0; j < room_width; j++)
            {
                if (final_positions[i][j] > 0)
                {
                    printf("#"); //, final_positions[i][j]);
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }

        scanf("%*c");
    }

    fclose(fptr);

    return 0;
}
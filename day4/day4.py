import re

file = open('day4.txt', 'r')

lines = file.readlines()

line_count = len(lines)
col_count = len(lines[0])

def check_for_mas(row, col):
    # if middle not a, return
    if lines[row+1][col+1] != 'A':
        return 0

    # verify that diagonals are MAS or SAM
    if (lines[row][col] == 'M' or lines[row][col] == 'S') and (lines[row+2][col+2] == 'S' or lines[row+2][col+2] == 'M') and (lines[row][col] != lines[row+2][col+2]):
        # other diagonal
        if (lines[row][col+2] == 'M' or lines[row][col+2] == 'S') and (lines[row+2][col] == 'S' or lines[row+2][col] == 'M') and (lines[row][col+2] != lines[row+2][col]):
            print(lines[row][col], lines[row][col+1], lines[row][col+2])
            print(lines[row+1][col], lines[row+1][col+1], lines[row+1][col+2])
            print(lines[row+2][col], lines[row+2][col+1], lines[row+2][col+2])
            return 1 
        
    return 0
        
total = 0
for row in range(0, line_count - 2):
    for col in range(0, col_count - 2):
        total += check_for_mas(row, col)

print(total)
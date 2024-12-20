#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fptr;
    fptr = fopen("day17.txt", "r");

    int registers[3] = {0, 0, 0};

    char str;
    int val;
    int i = 0;
    while (fscanf(fptr, "Register %c: %d\n", &str, &val) == 2)
    {
        registers[i] = val;
        i++;
    }

    fscanf(fptr, "\nProgram:");    

    // scan sequence of numbers
    int program[24];
    char ch;
    int program_count = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (isdigit(ch))
        {
            program[program_count] = ch - '0';
            program_count++;
        }
    }
    
    printf("Registers: %d %d %d\n", registers[0], registers[1], registers[2]);
    printf("Program count: %d\n", program_count);

    int instruction_pointer = 0;

    while (instruction_pointer < program_count) {
        int instruction = program[instruction_pointer];
        int operand = program[instruction_pointer + 1];
        switch (instruction) {
            // The adv instruction (opcode 0) performs division. The numerator is the value in the A register. 
            // The denominator is found by raising 2 to the power of the instruction's combo operand. 
            // (So, an operand of 2 would divide A by 4 (2^2); an operand of 5 would divide A by 2^B.) 
            // The result of the division operation is truncated to an integer and then written to the A register.
            case 0:
                int numerator = registers[0];
                if (operand > 3) {
                    operand = registers[operand - 4];
                }
                registers[0] = numerator / (1 << operand);
                break;
            // The bxl instruction (opcode 1) calculates the bitwise XOR of register B 
            // and the instruction's literal operand, then stores the result in register B.
            case 1:
                registers[1] = registers[1] ^ operand;
                break;
            // The bst instruction (opcode 2) calculates the value of its combo operand 
            // modulo 8 (thereby keeping only its lowest 3 bits), then writes that value to the B register.
            case 2:
                if (operand > 3) {
                    operand = registers[operand - 4];
                }
                registers[1] = operand % 8;
                break;
            // The jnz instruction (opcode 3) does nothing if the A register is 0. 
            // However, if the A register is not zero, it jumps by setting the instruction 
            // pointer to the value of its literal operand; if this instruction jumps, the 
            // instruction pointer is not increased by 2 after this instruction.
            case 3:
                if (registers[0] != 0)
                {
                    instruction_pointer = operand;
                    continue;
                }
                break;
            // The bxc instruction (opcode 4) calculates the bitwise XOR of register B and register C, 
            // then stores the result in register B. (For legacy reasons, this instruction reads an operand but ignores it.)
            case 4:
                registers[1] = registers[1] ^ registers[2];
                break;
            // The out instruction (opcode 5) calculates the value of its combo operand modulo 8, then outputs that value. 
            // (If a program outputs multiple values, they are separated by commas.)
            case 5:
                if (operand > 3) {
                    operand = registers[operand - 4];
                }
                printf("%d\n", operand % 8);
                break;
            // The bdv instruction (opcode 6) works exactly like the adv instruction except 
            // that the result is stored in the B register. (The numerator is still read from the A register.)
            case 6:
                if (operand > 3) {
                    operand = registers[operand - 4];
                }
                numerator = registers[0];
                registers[1] = numerator / (1 << operand);
                break;
            // The cdv instruction (opcode 7) works exactly like the adv instruction except 
            // that the result is stored in the C register. (The numerator is still read from the A register.)
            case 7:
                if (operand > 3) {
                    operand = registers[operand - 4];
                }
                numerator = registers[0];
                registers[2] = numerator / (1 << operand);
                break;
            default:
                printf("Unknown instruction: %d\n", instruction);
                break;
        }
        instruction_pointer += 2; // jump over combo/literal operand
    }

    fclose(fptr);   

    return 0;
}
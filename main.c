/**
File: RAL/S Interpreter Source Code

Author: Theodore Baker-Jones

Description: Source code for the RAL/S interpreter.

License: MIT License
**/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int add(int first_val, int second_val);
int subtract(int first_val, int second_val);
int multiply(int first_val, int second_val);
int divide(int first_val, int second_val);
int modulo(int first_val, int second_val);
int square_root(int val);
int set(int val);
int move(int src_var);
int print(int val);
int read();
int jump(int cond_var, int jmp_dest, int program_counter);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Argument expected");
    } else if (argc > 2) {
        printf("Too many arguments");
    } else {
        char character_output_tmp_var;
        int file_length_test = 0;
        //char fname[128];
        //fname = argv[1];
        FILE *programf;
        programf = fopen(argv[1], "r");
        if (!programf) { //if the file doesn't exist tell the user
            printf("Error: File does not exist");
            return 0;
        };
        int program_length = 0;
        while (!feof(programf)) {
            fscanf(programf, "%d", &file_length_test);
            program_length++;
        };

        int data_length;
        int program[program_length];
        int program_counter = 0;
        fclose(programf);
        programf = fopen(argv[1], "r");
        while (program_counter <= program_length) { //read into the program array
            fscanf(programf, "%d", &program[program_counter]);
            program_counter++;
        };

        program_counter = 0;
        data_length = program[program_counter];
        program_counter++;

        int data[data_length];
        while (program_counter < program_length) {
            switch (program[program_counter]) {
            case 1 :// addition
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 2] >= data_length) || (program[program_counter + 1] <= 0) || (program[program_counter + 2] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[program[program_counter + 1]] = add(data[program[program_counter + 1]], data[program[program_counter + 2]]);
                };
                break;
            case 2 : // subtraction
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 2] >= data_length) || (program[program_counter + 1] <= 0) || (program[program_counter + 2] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[program[program_counter + 1]] = subtract(data[program[program_counter + 1]], data[program[program_counter + 2]]);
                };
                break;
            case 3 : // multiplication
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 2] >= data_length) || (program[program_counter + 1] <= 0) || (program[program_counter + 2] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[program[program_counter + 1]] = multiply(data[program[program_counter + 1]], data[program[program_counter + 2]]);
                };
                break;
            case 4 : // division
                if (program[program_counter + 2] == 0) {
                    printf("Error: %d - Attempted divide by 0 \n", program_counter);
                    program_counter = program_length;
                } else if ((program[program_counter + 1] >= data_length) || (program[program_counter + 2] >= data_length) || (program[program_counter + 1] <= 0) || (program[program_counter + 2] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[program[program_counter + 1]] = divide(data[program[program_counter + 1]], data[program[program_counter + 2]]);
                };
                break;
            case 5 : // modulus
                if (program[program_counter + 2] == 0) {
                    printf("Error: %d - Attempted divide by 0 \n", program_counter);
                    program_counter = program_length;
                } else if ((program[program_counter + 1] >= data_length) || (program[program_counter + 2] >= data_length) || (program[program_counter + 1] <= 0) || (program[program_counter + 2] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                };
                break;
            case 6 : // square root
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 1] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[program[program_counter + 1]] = square_root(data[program[program_counter + 1]]);
                };
                break;
            case 7 : // set variable
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 1] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[program[program_counter + 1]] = program[program_counter + 2];
                };
                break;
            case 8 : // move variable
                if ((data[program[program_counter + 1]] >= data_length) || (data[program[program_counter + 2]] >= data_length) || (data[program[program_counter + 1]] <= 0) || (data[program[program_counter + 2]] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[data[program[program_counter + 1]]] = move(data[data[program[program_counter + 2]]]);
                };
                break;
            case 9 : // print
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 1] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    printf("%d ", data[program[program_counter + 1]]);
                };
                break;
            case 10 : // read
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 1] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else {
                    data[program[program_counter + 1]] = read();
                };
                break;
            case 11 : // jump if variable is negative
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 1] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                    program_counter = program_length;
                } else if ((program[program_counter + 2] >= data_length) || (program[program_counter + 2] < 0)) {
                    printf("Error: %d - Invalid jump destination", program_counter);
                    program_counter = program_length;
                } else {
                    program_counter = jump(data[program[program_counter + 1]], data[program[program_counter + 2]], program_counter);
                };
                break;
            case 12 : // end program
                program_counter = program_length;
                break;
            case 13: // prints a character
                if ((program[program_counter + 1] >= data_length) || (program[program_counter + 1] <= 0)) {
                    printf("Error: %d - Variable does not exist", program_counter);
                       } else {
                           character_output_tmp_var = (char)data[program[program_counter + 1]];
                           printf("%c", character_output_tmp_var);
                       };
                           break;
            default : // no valid command entered
                printf("Error: %d -  Command %d is invalid\n", program_counter, program[program_counter]);
                           program_counter = program_length;
                       };
                           program_counter += 3;
                       };
                       };
                           return 0;
                       };

                           int add(int first_val, int second_val) {
                           int result;
                           result = first_val + second_val;
                           return result;
                       };

                           int subtract(int first_val, int second_val) {
                           int result;
                           result = first_val - second_val;
                           return result;
                       };

                           int multiply(int first_val, int second_val) {
                           int result;
                           result = first_val * second_val;
                           return result;
                       };

                           int divide(int first_val, int second_val) {
                           int result;
                           result = (int) (first_val / second_val);
                           return result;
                       };

                           int modulo(int first_val, int second_val) {
                           int result;
                           result = first_val % second_val;
                           return result;
                       };

                           int square_root(int val) {
                           int dbl_val = (double) val;
                           int result;
                           result = (int) sqrt(dbl_val);
                           return result;
                       };

                           int set(int val) {
                           int result;
                           result = val;
                           return result;
                       };

                           int move(int src_var) {
                           int result;
                           result = src_var;
                           return result;
                       };

                           int print(int val) {
                           printf("%d \n", val);
                           return 0;
                       };

                           int read() {
                           int result;
                           scanf("%d", &result);
                           return result;
                       };

                           int jump(int cond_var, int jmp_dest, int program_counter) {
                           int jmp_result_counter;
                           jmp_result_counter = program_counter;
                           if (cond_var < 0) {
                           jmp_result_counter += (3 * jmp_dest);
                           if (jmp_dest < 0) {
                           jmp_result_counter -= 3;
                       };
                       };
                           return jmp_result_counter;
                       };

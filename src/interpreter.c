#include <assert.h>
#include <interpreter.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char read_instr_char(BFInterpreter *interpreter);
static void operation(BFInterpreter *interpreter, char c);
static void incr_pntr(BFInterpreter *interpreter);
static void decr_pntr(BFInterpreter *interpreter);
static void add_pntr_value(BFInterpreter *interpreter, int8_t value);
static void write_byte(BFInterpreter *interpreter);
static void read_byte(BFInterpreter *interpreter);
static void move_paired_bracket(BFInterpreter *interpreter);
static uint64_t search_paired_brakcet(BFInterpreter *interpreter, int8_t step);

typedef struct BFInterpreter {
        const char *instruction;
        uint64_t instr_index;
        char *memory;
        uint64_t mem_length;
        uint64_t mem_index;
} BFInterpreter;
void init_interpreter(BFInterpreter **interpreter) {
        *interpreter = malloc(sizeof(BFInterpreter));
        (*interpreter)->instruction = NULL;
        (*interpreter)->instr_index = 0;
        (*interpreter)->memory = calloc(300, sizeof(char));
        (*interpreter)->mem_index = 0;
        (*interpreter)->mem_length = 300;
}
void run(BFInterpreter *interpreter) {
        char c;
        while ((c = read_instr_char(interpreter))) {
                operation(interpreter, c);
                interpreter->instr_index++;
        }
}
void set_instruction(BFInterpreter *interpreter, const char *instruction) {
        const char *prev_instr = interpreter->instruction;
        uint64_t instr_length = strlen(instruction);

        interpreter->instruction = calloc(instr_length + 1, sizeof(char));
        memcpy((void *)interpreter->instruction, instruction, instr_length);

        if (prev_instr != NULL) free((void *)prev_instr);
}

static void operation(BFInterpreter *interpreter, char c) {
        switch (c) {
                case '+':
                        add_pntr_value(interpreter, 1);
                        break;
                case '-':
                        add_pntr_value(interpreter, -1);
                        break;
                case '<':
                        decr_pntr(interpreter);
                        break;
                case '>':
                        incr_pntr(interpreter);
                        break;
                case '[':
                        if (interpreter->memory[interpreter->mem_index] == 0) {
                                move_paired_bracket(interpreter);
                        }
                        break;
                case ']':
                        if (interpreter->memory[interpreter->mem_index] != 0) {
                                move_paired_bracket(interpreter);
                        }
                        break;
                case '.':
                        write_byte(interpreter);
                        break;
                case ',':
                        read_byte(interpreter);
                        break;
                default:
                        break;
        }
}
static void incr_pntr(BFInterpreter *interpreter) {
        interpreter->mem_index++;
        if (interpreter->mem_index < interpreter->mem_length) {
                return;
        }
        uint64_t new_length = interpreter->mem_length * 2;
        char *tmp = interpreter->memory;

        interpreter->memory = calloc(new_length, sizeof(char));
        memcpy(interpreter->memory, tmp, interpreter->mem_length);
        interpreter->mem_length = new_length;
        free(tmp);
}
static void decr_pntr(BFInterpreter *interpreter) {
        assert(interpreter->mem_index > 0);
        interpreter->mem_index--;
}
static void add_pntr_value(BFInterpreter *interpreter, int8_t value) {
        interpreter->memory[interpreter->mem_index] += value;
}
static void write_byte(BFInterpreter *interpreter) {
        putchar(interpreter->memory[interpreter->mem_index]);
}
static void read_byte(BFInterpreter *interpreter) {
        interpreter->memory[interpreter->mem_index] = getchar();
}
static void move_paired_bracket(BFInterpreter *interpreter) {
        int8_t step =
            interpreter->instruction[interpreter->instr_index] == '[' ? 1 : -1;
        interpreter->instr_index = search_paired_brakcet(interpreter, step);
}
static uint64_t search_paired_brakcet(BFInterpreter *interpreter, int8_t step) {
        int64_t bracket_count = 0;
        uint64_t index = interpreter->instr_index;
        do {
                if (interpreter->instruction[index] == '[') {
                        bracket_count++;
                } else if (interpreter->instruction[index] == ']') {
                        bracket_count--;
                }
                index += step;
        } while (bracket_count != 0);
        return index;
}
static char read_instr_char(BFInterpreter *interpreter) {
        return interpreter->instruction[interpreter->instr_index];
}
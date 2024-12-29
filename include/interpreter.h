#ifndef INTERPRETER_H_
#define INTERPRETER_H_
typedef struct BFInterpreter BFInterpreter;
void init_interpreter(BFInterpreter **interpreter);
void run(BFInterpreter *interpreter);
void set_instruction(BFInterpreter *interpreter, const char *instruction);
#endif
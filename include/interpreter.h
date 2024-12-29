#ifndef INTERPRETER_H_
#define INTERPRETER_H_
typedef struct BFInterpreter BFInterpreter;
void init_interpreter(BFInterpreter **interpreter, const char *instruction);
void run(BFInterpreter *interpreter);
#endif
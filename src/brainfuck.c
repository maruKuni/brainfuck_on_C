#include <interpreter.h>
#include <stdio.h>
#include <string.h>

int main() {
        char buf[256] = {'\0'};
        BFInterpreter *interpreter;
        init_interpreter(&interpreter);
        printf("$");
        while (scanf("%s", buf) > 0) {
                set_instruction(interpreter, buf);
                run(interpreter);
                memset(buf, 0, sizeof(char) * 256);
                printf("\n$");
        }

        return 0;
}
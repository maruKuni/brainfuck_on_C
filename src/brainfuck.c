#include <interpreter.h>

int main() {
        BFInterpreter *interpreter;
        init_interpreter(
            &interpreter,
            "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++.."
            "+++.>>.<-.<.+++.------.--------.>>+.>++.");
        run(interpreter);
        return 0;
}
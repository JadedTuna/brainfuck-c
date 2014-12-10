#define MEMSIZE  65535
#define TAPESIZE 30000
unsigned char memory[MEMSIZE];
unsigned char bracemap[MEMSIZE];
unsigned int temp_stack[MEMSIZE];
unsigned char tape[TAPESIZE];
unsigned int pointer, pc, sp;
char running, opcode;

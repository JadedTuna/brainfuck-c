#define MEMSIZE  65535
#define TAPESIZE 30000
unsigned int memory[MEMSIZE];
unsigned int bracemap[MEMSIZE];
unsigned int temp_stack[MEMSIZE];
unsigned char tape[TAPESIZE];
unsigned int pointer, pc, sp;
char running, opcode;

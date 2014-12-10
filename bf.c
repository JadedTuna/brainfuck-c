/*
 * Brainfuck interpreter written in C.
 * Report any bugs to http://github.com/Vik2015/brainfuck-c/issues/new
 * 
 * Written by Victor Kindhart.
 */
#include <stdio.h>
#include <stdlib.h>
#include "bf.h"

void die(char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

void load_rom(FILE* fp) {
    int i, c;
    for (i=0; (c = fgetc(fp)) != EOF; i++) {
        if (i >= MEMSIZE) die("error: memory overflow");
        memory[i] = c;
    }
}

void build_bracemap() {
    int i, start, c;
    for (i=0, sp=0; (c = memory[i]) != '\0'; i++) {
        switch (c) {
            case '[':
                temp_stack[sp++] = i;
                break;
            case ']':
                if (!sp) die("error: unbalanced braces");
                start = temp_stack[--sp];
                bracemap[start] = i;
                bracemap[i] = start;
                break;
        }
    }
    if (sp) die("error: unbalanced braces");
}

main(int argc, char* argv[]) {
    if (argc != 2) die("usage: bf <FILE>");
    FILE* fp = fopen(argv[1], "rb");
    if (!fp) die("error: failed to open file");
    load_rom(fp);
    build_bracemap();
    running = 1;
    for (;;) {
        if (pc >= MEMSIZE) break;
        if (!running) break;
        opcode = memory[pc];
        switch (opcode) {
            case 0:
                running = 0;
                break;
            case '>':
                pointer++;
                if (pointer > TAPESIZE) die("error: pointer too large");
                break;
            case '<':
                pointer--;
                if (pointer < 0) die("error: pointer too small");
                break;
            case '+':
                tape[pointer]++;
                break;
            case '-':
                tape[pointer]--;
                break;
            case '.':
                printf("%c", tape[pointer]);
                break;
            case ',':
                break;
            case '[':
                if (tape[pointer] == 0)
                    pc = bracemap[pc];
                break;
            case ']':
                if (tape[pointer] != 0)
                    pc = bracemap[pc];
                break;
            default:
                break;
        }
        pc++;
    }
}

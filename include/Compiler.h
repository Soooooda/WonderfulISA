#ifndef COMPILER_H
#define COMPILER_H
#include "../include/simulator.hpp"
#define OPCODE_OFFSET 26
#define RD_OFFSET 19
#define RN_OFFSET 15
#define RM_OFFSET 11
#define IMMEDIATE_OFFSET 0
#define ADD 1<<OPCODE_OFFSET
#define SUB 4<<OPCODE_OFFSET
#define LOADI 11<<OPCODE_OFFSET
#define BRANCH 20<<OPCODE_OFFSET
#define STOREI 14<<OPCODE_OFFSET
#define HALT 31<<OPCODE_OFFSET

class Compiler
{
    public:
        Compiler();
        string get_machine_code(string s);
};

#endif // COMPILER_H

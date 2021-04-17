#ifndef COMPILER_H
#define COMPILER_H
#include "../include/simulator.hpp"
#define OPCODE_OFFSET 26
#define RD_OFFSET 19
#define RN_OFFSET 15
#define RM_OFFSET 11
#define IMMEDIATE_OFFSET 0
#define ADD 1<<OPCODE_OFFSET
#define ADDI 2<<OPCODE_OFFSET
#define SUB 4<<OPCODE_OFFSET
#define SUBI 5<<OPCODE_OFFSET
#define LOAD 10<<OPCODE_OFFSET
#define LOADI 11<<OPCODE_OFFSET
#define STORE 13<<OPCODE_OFFSET
#define STOREI 14<<OPCODE_OFFSET
#define AND 16<<OPCODE_OFFSET
#define OR 17<<OPCODE_OFFSET
#define NOT 18<<OPCODE_OFFSET
#define XOR 19<<OPCODE_OFFSET
#define BRANCH 20<<OPCODE_OFFSET
#define JUMP 21<<OPCODE_OFFSET
#define HALT 31<<OPCODE_OFFSET
#define BRANCH_FLAG_OFFSET 8

class Compiler
{
    public:
        Compiler();
        int32_t get_machine_code(string s);
        int32_t proccess_add(vector<string> tokens);
        int32_t proccess_sub(vector<string> tokens);
        int32_t proccess_load(vector<string> tokens);
        int32_t proccess_branch(vector<string> tokens);
        int32_t proccess_halt(vector<string> tokens);
        int32_t proccess_store(vector<string> tokens);
        int32_t proccess_bit(vector<string> tokens);
};

#endif // COMPILER_H

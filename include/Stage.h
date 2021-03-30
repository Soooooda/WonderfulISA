#ifndef STAGE_H
#define STAGE_H
#include "../include/simulator.hpp"
#include <queue>
#include "Register.h"
//template<class T>
struct instruction
{
    int16_t instruction_operator;
    int16_t operands[3];
    int16_t address;
    int16_t cmp;
};

struct output
{
    bool    changed;
    int16_t register_id;
    int16_t address;
    int16_t value;
    instruction inst;
};

class Stage
{
    public:
        Stage();
        //virtual void execute() = 0;
        //queue<T> instruction_queue;
        int16_t cost_time;
};

#endif // STAGE_H

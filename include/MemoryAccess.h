#ifndef MEMORYACCESS_H
#define MEMORYACCESS_H
# include "../include/Stage.h"
# include "simulator.hpp"
# include "Register.h"
class MemoryAccess: public Stage
{
    public:
        MemoryAccess();
        output *execute(Simulator* simulator, Register* registe);
        queue<output *> mem_queue;
        output result;
        int16_t time;

};
#endif // MEMORYACCESS_H

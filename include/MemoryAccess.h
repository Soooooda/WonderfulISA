#ifndef MEMORYACCESS_H
#define MEMORYACCESS_H
# include "../include/Stage.h"
# include "simulator.hpp"
class MemoryAccess: public Stage
{
    public:
        MemoryAccess();
        output *execute(Simulator* simulator);
        queue<output*> mem_queue;
        output result;
        int16_t time;

};
#endif // MEMORYACCESS_H

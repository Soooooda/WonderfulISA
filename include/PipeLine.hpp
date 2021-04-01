#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include "Decode.h"
#include "Execute.h"
#include "Fetch.h"
#include "MemoryAccess.h"
#include "WriteBack.h"
#include "../include/simulator.hpp"

class PipeLine
{
    public:
        PipeLine();
        Simulator simulator;
        int16_t pc;
        string* instructions;
        void read_instructions(string* s);
        void run_cycle();
        void initialize(string* s, int16_t size);
        Fetch fetch;
        Decode decode;
        Execute execute;
        MemoryAccess memoryaccess;
        WriteBack writeback;
        Register registe;
        int16_t instruction_count;
        int16_t pipeLine_pc[5];
        string getLastElement (const std::string& str);
        void record_pipeline();
};
#endif

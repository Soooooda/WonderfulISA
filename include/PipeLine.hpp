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
        void readInstruction(string s);
        int16_t pc;
        string* instructions;
        void read_instructions(string* s);
        void run_cycle();
        void initialize(string* s);
        Fetch fetch;
        Decode decode;
        Execute execute;
        MemoryAccess memoryaccess;
        WriteBack writeback;
        Register registe;
        output *wb_output;
        output *alu_result;
        output *decode_result;


};
#endif

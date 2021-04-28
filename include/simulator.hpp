#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP


#include "../include/cache.hpp"
#define BLOCK_OFFSET ((1<<16)-4)
#define ADDRESS_OFFSET 3
using namespace std;
class Simulator
{
    public:
        int16_t *memory;
        Cache l1_cache;
        Cache l2_cache;
        Simulator();
        string write_memory(int16_t address, int16_t value);
        string write_instruction(int16_t address, int16_t value);
        int16_t read_memory(int16_t address);
        int16_t read_instruction(int16_t address);
        void instantiate();
};
#endif // SIMULATOR_HPP

#include "../include/Register.h"

Register::Register()
{
    for(int16_t i = 0;i<16;i++)
    {
        registers[i] = 0;
        flags[i] = 0;
    }
}

int16_t Register::get(int16_t index)
{
    return registers[index];
}
int16_t Register::getflag(int16_t index)
{
    return flags[index];
}
void Register::set(int16_t index, int16_t value)
{
    registers[index] = value;
}

void Register::add(int16_t index)
{
    flags[index]++;
}

void Register::min(int16_t index)
{
    flags[index]--;
}
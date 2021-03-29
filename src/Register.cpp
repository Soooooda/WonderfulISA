#include "../include/Register.h"

Register::Register()
{
    for(int16_t i = 0;i<16;i++)
    {
        registers[i] = 0;
    }
}

int16_t Register::get(int16_t index)
{
    return registers[index];
}

void Register::set(int16_t index, int16_t value)
{
    registers[index] = value;
}

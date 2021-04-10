#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>
class Register
{
    public:
        Register();
        int16_t registers[16];
        int16_t flags[16];
        int16_t get(int16_t index);
        int16_t getflag(int16_t index);
        void set(int16_t index, int16_t value);
        void add(int16_t index);
        void min(int16_t index);

};

#endif // REGISTER_H

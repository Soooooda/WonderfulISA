#ifndef DECODE_H
#define DECODE_H
# include "../include/Stage.h"
# include "Register.h"
class Decode: public Stage
{
    public:
        Decode();
        output *execute(Register *registe);
        queue<int32_t> decode_queue;

};
#endif // DECODE_H

#ifndef DECODE_H
#define DECODE_H
# include "../include/Stage.h"
class Decode: public Stage
{
    public:
        Decode();
        output *execute();
        queue<string> decode_queue;

};
#endif // DECODE_H

#ifndef FETCH_H
#define FETCH_H
# include "../include/Stage.h"
class Fetch: public Stage
{
    public:
        Fetch();
        int32_t execute(string *instructions, Simulator *simulator);
        queue<int16_t> fetch_queue;

};


#endif // FETCH_H

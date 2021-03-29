#ifndef FETCH_H
#define FETCH_H
# include "../include/Stage.h"
class Fetch: public Stage
{
    public:
        Fetch();
        string execute(string* instructions);
        queue<int16_t> fetch_queue;

};


#endif // FETCH_H

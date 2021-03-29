#ifndef EXECUTE_H
#define EXECUTE_H
# include "../include/Stage.h"
# include "Register.h"
class Execute: public Stage
{
    public:
        Execute();
        output * execute(Register registe);
        queue<output *> execute_queue;

};
#endif // EXECUTE_H

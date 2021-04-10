//#ifndef WRITEBACK_H
//#define WRITEBACK_H
//# include "../include/Stage.h"
//class WriteBack: public Stage
//{
//    public:
//        WriteBack();
//        void execute();
//        queue<int16_t> instruction_queue;

//};
//#endif // WRITEBACK_H

#ifndef WRITEBACK_H
#define WRITEBACK_H
# include "../include/Stage.h"
# include "Register.h"
class WriteBack: public Stage
{
    public:
        WriteBack();
        void execute(Register * registe);
        queue<output *> wb_queue;

};


#endif // FETCH_H

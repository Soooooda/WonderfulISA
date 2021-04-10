# include "../include/WriteBack.h"

WriteBack::WriteBack()
{

}

void WriteBack::execute(Register *registe)
{
    output *data = (struct output*)wb_queue.front();
    if(wb_queue.empty())
    {
        cout<<"mem skip"<<endl;
    }
    else
    {
        if(data->inst.instruction_operator == 1){//LOAD
            registe->set(data->inst.operands[0],data->value);
            registe->min(data->inst.operands[0]);

        }
        else if(data->inst.instruction_operator == 3){//ADD
            registe->set(data->inst.operands[0],data->value);
            registe->min(data->inst.operands[0]);
        }
        else if(data->inst.instruction_operator == 4){//Minus
            registe->set(data->inst.operands[0],data->value);
            registe->min(data->inst.operands[0]);
        }
    }
    //free(data);
    return;
}

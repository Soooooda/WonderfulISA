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
        int temp = data->inst.instruction_operator;
        if(temp != 13 && temp != 14 &&temp != 20 && temp != 21 && temp != 31){
            registe->set(data->inst.operands[0],data->value);
            registe->min(data->inst.operands[0]);

        }
        
    }
    //free(data);
    return;
}

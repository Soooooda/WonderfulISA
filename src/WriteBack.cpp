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
        if(temp != 13 && temp != 14 &&temp != 20 && temp != 21 && temp != 31 && temp != 12){
            registe->set(data->inst.operands[0],data->value);
            registe->min(data->inst.operands[0]);
            cout<<" Rd:"<<data->inst.operands[0]<<" value"<<data->value<<endl;

        }
        if(temp == 12){
            int type = data->inst.cmp;
            int row = registe->get(data->inst.operands[1]);
            int col = registe->get(data->inst.operands[2]);
            if (type == 0)
            {
                for(int i = 0; i < row; i++)
                {
                    registe->set_vector(type,i,data->vector[i]);
                }
                for(int i = row; i <50; i++)
                {
                    registe->set_vector(type,i,0);
                }
            }
            else
            {
                for(int i = 0; i < col; i++)
                {
                    registe->set_vector(type,i,data->vector[i]);
                }
                for(int i = col; i <50; i++)
                {
                    registe->set_vector(type,i,0);
                }
            }
        for(int i=0;i<50;i++){
            cout<<" "<<registe->getvector(0,i);
        }
        for(int i=0;i<50;i++){
            cout<<" "<<registe->getvector(1,i);
        }
        }
    }
    //free(data);
    return;
}

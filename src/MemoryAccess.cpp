# include "../include/MemoryAccess.h"

MemoryAccess::MemoryAccess()
{
    this->time = 0;
}

output *MemoryAccess::execute(Simulator* simulator, Register* registe, int model)
{
    if(mem_queue.empty())
    {
        cout<<"mem skip"<<endl;
        return NULL;
    }
    output *data = (struct output*) mem_queue.front();
    if (this->time == 0) {
        cout<<"Mem Opt:"<<data->inst.instruction_operator <<endl;
        if (data->inst.instruction_operator == 10)//LOAD
        {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 3){
                simulator->read_memory(registe->get(data->inst.operands[1]));
                cout<<"Start Store"<<endl;
                this->time = 3;
            }
            else{
                simulator->read_memory(registe->get(data->inst.operands[1]));
                cout<<"Start Store"<<endl;
                this->time = 1;
            }
        } 
        else if (data->inst.instruction_operator == 11) //LOADI
        {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 3){
                data->value = simulator->read_memory(data->inst.address);
                cout<<"Start Load"<<endl;
                this->time = 3;
            }
            else{
                data->value = simulator->read_memory(data->inst.address);
                cout<<"Start Load"<<endl;
                this->time = 1;
            }
        }
        else if (data->inst.instruction_operator == 12)//LOADV
        
            int type = data->inst.cmp;//0 load row, 1 laod column
            int row = registe->get(data->inst.operands[1]);
            int col = registe->get(data->inst.operands[2]);
            int init_address = registe->get(data->inst.operands[0]);
            if(type == 0)
            {
                for(int i = 0; i < row; i++){
                    if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 3){
                        data->vector[i]= simulator->read_memory(init_address);
                        init_address++;
                        this->time+=3;
                    }
                    else{
                        data->vector[i] = simulator->read_memory(data->inst.address);
                        init_address++;
                        this->time++;
                    }
                }
            }
            else if(type == 1)
            {
                for(int i = 0; i < col; i++){
                    if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 3){
                        data->vector[i]= simulator->read_memory(init_address);
                        init_address += row;
                        this->time+=3;
                    }
                    else{
                        data->vector[i] = simulator->read_memory(data->inst.address);
                        init_address += row ;
                        this->time++;
                    }
                }
            }

        }  
        else if (data->inst.instruction_operator == 13)//STORE
        {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 3){
                int16_t address = registe->get(data->inst.operands[1]);
                simulator->write_memory(address, registe->get(data->inst.operands[0]));
                cout<<"Start Store"<<endl;
                this->time = 3;
            }
            else{
                int16_t address = registe->get(data->inst.operands[1]);
                simulator->write_memory(address, registe->get(data->inst.operands[0]));
                cout<<"Start Store"<<endl;
                this->time = 1;
            }
        }
        else if (data->inst.instruction_operator == 14)//STOREI
        {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 3){
                simulator->write_memory(data->inst.address, registe->get(data->inst.operands[0]));
                cout<<"Start Store"<<endl;
                this->time = 3;
            }
            else{
                simulator->write_memory(data->inst.address, registe->get(data->inst.operands[0]));
                cout<<"Start Store"<<endl;
                this->time = 1;
            }
        }
        else {
            return data;
        }
    }
    this->time--;

    cout<<"mem time"<<this->time<<endl;
    if (this->time == 0) {
        if(data->inst.instruction_operator == 1){
            //registe->set(data->inst.operands[0],data->value);
        }
        return data;
    }
    return NULL;
}

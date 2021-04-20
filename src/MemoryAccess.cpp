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

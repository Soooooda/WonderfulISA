# include "../include/MemoryAccess.h"

MemoryAccess::MemoryAccess()
{
    this->time = 0;
}

output *MemoryAccess::execute(Simulator* simulator, Register* registe)
{
    if(mem_queue.empty())
    {
        cout<<"mem skip"<<endl;
        return NULL;
    }
    output *data = (struct output*) mem_queue.front();
    if (this->time == 0) {
        cout<<"Mem Opt:"<<data->inst.instruction_operator <<endl;
        if (data->inst.instruction_operator == 1) {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1){
                data->value = simulator->read_memory(data->inst.address);
                cout<<"Start Load"<<endl;
                this->time = 3;
            }
            else{
                data->value = simulator->read_memory(data->inst.address);
                cout<<"Start Load"<<endl;
                this->time = 1;
            }
        } else if (data->inst.instruction_operator == 2)
        {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1){
                simulator->write_memory(data->inst.address, registe->get(data->inst.operands[0]));
                cout<<"Start Store"<<endl;
                this->time = 3;
            }
            else{
                simulator->write_memory(data->inst.address, registe->get(data->inst.operands[0]));
                cout<<"Start Store"<<endl;
                this->time = 1;
            }
        } else {
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

# include "../include/MemoryAccess.h"

MemoryAccess::MemoryAccess()
{
    this->time = 0;
}

output *MemoryAccess::execute(Simulator* simulator)
{
    if(mem_queue.empty())
    {
        return NULL;
    }
    output *data = mem_queue.front();
    if (this->time == 0) {
        cout<<"here mem! "<<data->inst.instruction_operator <<endl;
        if (data->inst.instruction_operator == "LOAD") {
            data->value = simulator->read_memory(data->inst.operands[0]);
            cout<<"load here"<<endl;

        } else if (data->inst.instruction_operator == "STORE")
        {
            simulator->write_memory(data->inst.address, data->inst.operands[0]);
            cout<<"store here"<<endl;
        }
        this->time = 3;
    }

    this->time--;
    if (this->time == 0) {
        mem_queue.pop();
        return data;
    }
    return NULL;
}

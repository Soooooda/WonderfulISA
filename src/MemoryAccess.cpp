# include "../include/MemoryAccess.h"

MemoryAccess::MemoryAccess()
{
    time = 0;
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
            if(simulator->l1_cache.request_cache(registe->get(data->inst.operands[1])) == -1 || model == 1 || model == 2){
                data->value = simulator->read_memory(registe->get(data->inst.operands[1]));
                //cout<<"Start LAOD"<<endl;
                //cout<<"cache:"<<simulator->l1_cache.request_cache(registe->get(data->inst.operands[1]))<<endl;
                //cout<<"model:"<<model<<endl;
                time = 100;
            }
            else{
                data->value = simulator->read_memory(registe->get(data->inst.operands[1]));
                cout<<"Start LOAD!!!!!"<<endl;
                time = 1;
            }
        } 
        else if (data->inst.instruction_operator == 11) //LOADI
        {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 2){
                data->value = simulator->read_memory(data->inst.address);
                //cout<<"Start Load"<<endl;
                time = 100;
            }
            else{
                data->value = simulator->read_memory(data->inst.address);
                cout<<"Start Load!!!!!!"<<endl;
                time = 1;
            }
        }
        else if (data->inst.instruction_operator == 12)//LOADV
        {
            //0 load row, 1 laod column
            int type = data->inst.cmp;
            int row = registe->get(data->inst.operands[1]);
            int col = registe->get(data->inst.operands[2]);
            int init_address = registe->get(data->inst.operands[0]);
            if( type == 0)
            {
                for(int i = 0; i < row; i++){
                    if(simulator->l1_cache.request_cache(init_address) == -1 || model == 1 || model == 2){
                        data->vector[i]= simulator->read_memory(init_address);
                        init_address++;
                        time+=100;
                    }
                    else{
                        data->vector[i] = simulator->read_memory(init_address);
                        init_address++;
                        time++;
                    }
                }
            }
            else if(type == 1)
            {
                for(int i = 0; i < col; i++){
                    if(simulator->l1_cache.request_cache(init_address) == -1 || model == 1 || model == 2){
                        data->vector[i]= simulator->read_memory(init_address);
                        init_address += row;
                        time+=100;
                    }
                    else{
                        data->vector[i] = simulator->read_memory(init_address);
                        init_address += row ;
                        time++;
                    }
                }
            }

        }  
        else if (data->inst.instruction_operator == 13)//STORE
        {
            int16_t address = registe->get(data->inst.operands[1]);
            if(simulator->l1_cache.request_cache(address) == -1 || model == 1 || model == 2){
                simulator->write_memory(address, registe->get(data->inst.operands[0]));
                //cout<<"Start Store"<<endl;
                cout<<"cache:"<<simulator->l1_cache.request_cache(registe->get(data->inst.operands[1]))<<endl;
                cout<<"model:"<<model<<endl;
                cout<<"address:"<<address<<endl;
                time = 100;
            }
            else{
                simulator->write_memory(address, registe->get(data->inst.operands[0]));
                cout<<"Start Store!!!!!"<<endl;
                time = 1;
            }
        }
        else if (data->inst.instruction_operator == 14)//STOREI
        {
            if(simulator->l1_cache.request_cache(data->inst.address) == -1 || model == 1 || model == 2){
                simulator->write_memory(data->inst.address, registe->get(data->inst.operands[0]));
                //cout<<"Start Store"<<endl;
                time = 100;
            }
            else{
                simulator->write_memory(data->inst.address, registe->get(data->inst.operands[0]));
                cout<<"Start Store!!!!!"<<endl;
                time = 1;
            }
        }
        else {
            return data;
        }
    }
    time--;

    cout<<"mem time"<<this->time<<endl;
    if (time == 0) {
        if(data->inst.instruction_operator == 1){
            //registe->set(data->inst.operands[0],data->value);
        }
        return data;
    }
    return NULL;
}
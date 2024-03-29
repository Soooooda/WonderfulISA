# include "../include/Fetch.h"

Fetch::Fetch()
{
    clear(fetch_queue);
}

int32_t Fetch::execute(Simulator *simulator)
{
    int16_t base = 100;
    if(fetch_queue.empty())
    {
        cout<<"fetch skip"<<endl;
        return -1;
    }
    int16_t pc = fetch_queue.front();
    cout<<"pc:"<<pc<<endl;
    fetch_queue.pop();
    int16_t part1 = simulator->read_memory(base+pc*2);
    int16_t part2 = simulator->read_memory(base+pc*2+1);
    int32_t temp_instruction = 0;
    if(part2<0){
        int32_t temp = (~part2);
        temp = (~temp)&(0x0000ffff);
        temp_instruction = (part1<<16) + temp;
    }
    else{
        temp_instruction = (part1<<16) + part2;
    }

    return temp_instruction;
}

//load r1 &0x22
//load r2 &0x44
//add r3 r1 r2
//store r2 &0x11
#include "../include/PipeLine.hpp"

PipeLine::PipeLine()
{
    pc =  0;
}

void PipeLine::read_instructions(string *s)
{
    instructions = s;
}

void PipeLine::initialize(string* s, int16_t size)
{
    read_instructions(s);
    fetch.fetch_queue.push(pc);
    this->instruction_count = size;
}

void PipeLine::run_cycle()
{    
    cout<<"==write back=="<<endl;

    cout<<"==memory access=="<<endl;
    output *wb_result = memoryaccess.execute(&simulator, &registe);
    if(wb_result)
    {
        memoryaccess.mem_queue.pop();
        writeback.wb_queue.push(wb_result);

    }
    if(memoryaccess.time>0){
        return;
    }

    cout<<"==alu execute=="<<endl;
    output *alu_result = execute.execute(&registe);
    if(alu_result)
    {
        execute.execute_queue.pop();
        memoryaccess.mem_queue.push(alu_result);

    }

    cout<<"==decode=="<<endl;
    struct output *result = decode.execute();
    cout<<"decode address:"<<result<<endl;
    if(result)
    {
        execute.execute_queue.push(result);
    }

    cout<<"==fetch=="<<endl;
    string fetch_result = fetch.execute(instructions);
    if(fetch_result!="")
    {
        decode.decode_queue.push(fetch_result);
    }


    if(pc < instruction_count)
    {
//        if(pc >= short(instructions->size())){
//            return;
//        }
        fetch.fetch_queue.push(pc);
        pc+=1;
    }

    cout<<"==finish==\n\n"<<endl;

}

//fetch from pc

//if branch compare and change pc
//decode to 0101
//result: instruction

//calculate if needed from decode
//result: value


//load and store from decode
//result: value

//write to register
//from alu and memory
//write back!


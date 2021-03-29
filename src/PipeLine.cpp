//load r1 &0x22
//load r2 &0x44
//add r3 r1 r2
//store r2 &0x11
#include "../include/PipeLine.hpp"

PipeLine::PipeLine()
{
    pc =  0;
}


void PipeLine::readInstruction(string s)
{
    cout<<s<<endl;
}

void PipeLine::read_instructions(string *s)
{
    instructions = s;
}

void PipeLine::initialize(string* s)
{
    read_instructions(s);
    fetch.fetch_queue.push(pc);
}

void PipeLine::run_cycle()
{
    cout<<"==1=="<<pc<<short(instructions->size())<<endl;
//    if()
//    {


        cout<<"==2=="<<endl;
        // writeback oper
        output *wb_output = memoryaccess.execute(&simulator);
        if(wb_output!=NULL)
        {
            writeback.wb_queue.push(wb_output);
        }

        // excute oper
        output* alu_result = execute.execute(registe);
        if(alu_result)
        {
            memoryaccess.mem_queue.push(alu_result);
        }

        //decode oper
        output* decode_result = decode.execute();

        if(decode_result)
        {
            execute.execute_queue.push(decode_result);
        }

        // fetch oper
        string fetch_result = fetch.execute(instructions);
        if(fetch_result!="")
        {
            decode.decode_queue.push(fetch_result);
        }
        if(pc < short(instructions->size()))
        {
            fetch.fetch_queue.push(pc);
            pc+=1;
        }

        cout<<"==3=="<<endl;

        cout<<"==4=="<<endl;

//    }
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


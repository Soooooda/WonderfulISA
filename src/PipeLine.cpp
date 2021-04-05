//load r1 &0x22
//load r2 &0x44
//add r3 r1 r2
//store r2 &0x11
#include "../include/PipeLine.hpp"

PipeLine::PipeLine()
{
    pc =  0;
    for(int16_t i = 0; i<5; i++)
    {
        pipeLine_pc[i] = 0;
    }
}

void PipeLine::read_instructions(string *s, int16_t size)
{
    instructions = s;
    int16_t base = 100;
    for(int16_t i = 0; i < size; i++)
    {   int32_t ins= 0;
        for(int j = 0; j < 32; j++){
            ins = ins*2 + stoi(instructions[i].substr(j,1));
        }
        int16_t part2 = ins&0x0000ffff;
        int16_t part1 =(ins >>8);
        simulator.write_memory(base+i,part1);
        simulator.write_memory(base +i +1,part2);
    }
}

void PipeLine::initialize(string* s, int16_t size)
{
    read_instructions(s,size);
//    fetch.fetch_queue.push(pc);
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
    else
    {
        record_pipeline();
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
    string fetch_result = fetch.execute(instructions,&simulator);
    if(fetch_result!="")
    {
        decode.decode_queue.push(fetch_result);
    }

    if(pc < instruction_count)
    {
        fetch.fetch_queue.push(pc);
        pc+=1;
    }
    cout<<"==finish==\n\n"<<endl;

    record_pipeline();

}


string PipeLine::getLastElement (const std::string& str)
{
  cout << "Splitting: " << str << '\n';
  size_t found = str.find_last_of(" ");
  cout << " file: " << str.substr(found+1) << '\n';
  return str.substr(found+1);
}

void PipeLine::record_pipeline()
{
    if(fetch.fetch_queue.empty())
        pipeLine_pc[0] = -1;
    else
        pipeLine_pc[0] = fetch.fetch_queue.front();
    if(decode.decode_queue.empty())
        pipeLine_pc[1] = -1;
    else
        pipeLine_pc[1] = stoi(getLastElement(decode.decode_queue.front()));
    if(execute.execute_queue.empty())
        pipeLine_pc[2] = -1;
    else
        pipeLine_pc[2] = execute.execute_queue.front()->pc;
    if(memoryaccess.mem_queue.empty())
        pipeLine_pc[3] = -1;
    else
        pipeLine_pc[3] = memoryaccess.mem_queue.front()->pc;
    if(writeback.wb_queue.empty())
        pipeLine_pc[4] = -1;
    else
        pipeLine_pc[4] = writeback.wb_queue.front()->pc;

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


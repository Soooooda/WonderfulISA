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
        pipeLine_pc[i] = "0";
    }
}

void PipeLine::read_instructions(string *s, int16_t size, int32_t* machine_code)
{
    instructions = s;
    int16_t base = 100;
    for(int16_t i = 0; i < size; i++)
    {
        int32_t ins = compiler.get_machine_code(instructions[i]);
        machine_code[i] = ins;
//        string binary = std::bitset<32>(ins).to_string();
//        cout<<binary<<endl;
        int32_t temp_part1 =ins >>16;
        int16_t part1 = temp_part1;
        cout<<"part1: "<<part1<<endl;
        cout<<"ins"<<ins<<endl;
        int16_t part2 = ins&0x0000ffff;
        cout<<"part2: "<<part2<<endl;
        simulator.write_memory(base+i*2,part1);
        simulator.write_memory(base +i*2 +1,part2);
    }
}

void PipeLine::initialize(string* s, int16_t size, int32_t* machine_code)
{
    read_instructions(s,size, machine_code);
    this->instruction_count = size;
}

void PipeLine::run_cycle(int model)
{    

    cout<<"==write back=="<<endl;
    if(!writeback.wb_queue.empty()){
        if (writeback.wb_queue.front()->inst.instruction_operator == 31){
            pc = -1;
        }
        else{
            writeback.execute(&registe);
        }
        writeback.wb_queue.pop();
    }
    cout<<"==memory access=="<<endl;
    output *ma_result = memoryaccess.execute(&simulator, &registe, model);
    if(ma_result)
    {
        memoryaccess.mem_queue.pop();
        writeback.wb_queue.push(ma_result);

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
        if(alu_result->inst.instruction_operator == 21)
        {
            cout<<"Now Jump！";
            while(!execute.execute_queue.empty()){
                execute.execute_queue.pop();
            }
            while(!decode.decode_queue.empty()){
                decode.decode_queue.pop();
            }
            while(!fetch.fetch_queue.empty()){
                fetch.fetch_queue.pop();
            }
            pc = alu_result->inst.address;
        }
        else if (alu_result->inst.instruction_operator == 20)
        {
            cout<< "Now Branch"<<endl;
            switch (alu_result->inst.cmp)
            {
                case 0: //equal with immediate
                    cout<< "branch with qural"<<endl;
                    if(registe.getflag(alu_result->inst.operands[1])!= 0 || registe.getflag(alu_result->inst.operands[2])!= 0){
                        cout<<"Not finished for R"<< alu_result->inst.operands[1]<<":"<<registe.getflag(alu_result->inst.operands[1])<<" R"<<alu_result->inst.operands[2]<<":"<<registe.getflag(alu_result->inst.operands[2])<<endl;
                        return;
                    }
                    else if(registe.get(alu_result->inst.operands[1]) == registe.get(alu_result->inst.operands[2]))
                    {
                        /*while(!execute.execute_queue.empty()){
                            execute.execute_queue.pop();
                        }*/
                        while(!decode.decode_queue.empty()){
                            decode.decode_queue.pop();
                        }
                        while(!fetch.fetch_queue.empty()){
                            fetch.fetch_queue.pop();
                        }
                        cout<<"The new pc:"<<pc<<"   "<<alu_result->inst.address<<endl;
                        if(model == 4 || model == 2)
                        {
                            pc = pc-3 + alu_result->inst.address;
                        }
                        else{
                            pc = pc-1 + alu_result->inst.address;
                        }
                    }
                    break;
                case 1://larger or equal with immediate jump
                    cout<<"branch with larger"<<endl;
                    if(registe.getflag(alu_result->inst.operands[1])!= 0 || registe.getflag(alu_result->inst.operands[2])!= 0){
                        cout<<"Not finished for R"<< alu_result->inst.operands[1]<<":"<<registe.getflag(alu_result->inst.operands[1])<<" R"<<alu_result->inst.operands[2]<<":"<<registe.getflag(alu_result->inst.operands[2])<<endl;

                        return;
                    }
                    else if(registe.get(alu_result->inst.operands[1]) <= registe.get(alu_result->inst.operands[2]))
                    {
                        /*while(!execute.execute_queue.empty()){
                            execute.execute_queue.pop();
                        }*/
                        while(!decode.decode_queue.empty()){
                            decode.decode_queue.pop();
                        }
                        while(!fetch.fetch_queue.empty()){
                            fetch.fetch_queue.pop();
                        }
                        cout<<"The new pc:"<<pc<<"   "<<alu_result->inst.address<<endl;
                        if(model == 4 || model == 2)
                        {
                            pc = pc-3 + alu_result->inst.address;
                        }
                        else{
                            pc = pc-1 + alu_result->inst.address;
                        }
                    }
                    break;
                case 2://larger with immediate jump
                    cout<<"branch with larger or equal"<<endl;
                    if(registe.getflag(alu_result->inst.operands[1])!= 0 || registe.getflag(alu_result->inst.operands[2])!= 0){
                        cout<<"Not finished for R"<< alu_result->inst.operands[1]<<":"<<registe.getflag(alu_result->inst.operands[1])<<" R"<<alu_result->inst.operands[2]<<":"<<registe.getflag(alu_result->inst.operands[2])<<endl;

                        return;
                    }
                    else if(registe.get(alu_result->inst.operands[1]) < registe.get(alu_result->inst.operands[2]))
                    {
                        /*while(!execute.execute_queue.empty()){
                            execute.execute_queue.pop();
                        }*/
                        while(!decode.decode_queue.empty()){
                            decode.decode_queue.pop();
                        }
                        while(!fetch.fetch_queue.empty()){
                            fetch.fetch_queue.pop();
                        }
                        cout<<"The new pc:"<<pc<<"   "<<alu_result->inst.address<<endl;
                        if(model == 4 || model == 2)
                        {
                            pc = pc-3 + alu_result->inst.address;
                        }
                        else{
                            pc = pc-1 + alu_result->inst.address;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        execute.execute_queue.pop();
        memoryaccess.mem_queue.push(alu_result);   

    }

    cout<<"==decode=="<<endl;
    struct output *result = decode.execute(&registe);
    cout<<"decode address:"<<result<<endl;
    if(result)
    {
        execute.execute_queue.push(result);
    }

    cout<<"==fetch=="<<endl;
    int32_t fetch_result = fetch.execute(&simulator);
    if(fetch_result!=-1)
    {
        decode.decode_queue.push(fetch_result);
    }

    if(pc != -1)//可以给个1000000000试试看
    {
        if(model == 2 || model == 4){
            fetch.fetch_queue.push(pc);
            pc+=1;
        }
        
        else{
            if(decode.decode_queue.empty()&& execute.execute_queue.empty() && memoryaccess.mem_queue.empty()&& writeback.wb_queue.empty())
            {
                fetch.fetch_queue.push(pc);
                pc+=1;
            }
        }
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
    string temp = "";
    if(fetch.fetch_queue.empty())
        pipeLine_pc[0] = "-1";
    else
        pipeLine_pc[0] = to_string(fetch.fetch_queue.front());
    if(decode.decode_queue.empty())
        pipeLine_pc[1] = "-1";
    else
    //我将decode的queue改成了int我不知道会对后面造成什么影响
        //pipeLine_pc[1] = getLastElement(to_string(decode.decode_queue.front()));
        pipeLine_pc[1] = to_string(decode.decode_queue.front());
    if(execute.execute_queue.empty())
        pipeLine_pc[2] = "-1";
    else
        pipeLine_pc[2] = execute.execute_queue.front()->ins_text;;
    if(memoryaccess.mem_queue.empty())
        pipeLine_pc[3] = "-1";
    else
        pipeLine_pc[3] = memoryaccess.mem_queue.front()->ins_text;
    if(writeback.wb_queue.empty())
        pipeLine_pc[4] = "-1";
    else
        pipeLine_pc[4] = writeback.wb_queue.front()->ins_text;
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


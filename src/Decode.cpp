# include "../include/Decode.h"

Decode::Decode()
{

}

output* Decode::execute(Register *registe)
{
    if(decode_queue.empty())
    {
        cout<<"decode skip"<<endl;
        return NULL;
    }
    output* result = (struct output *) malloc(sizeof(output));
    int32_t instrut = decode_queue.front();
    int32_t opcode = (instrut & 0x7c000000)>>26;
    int32_t Rd = (instrut & 0x00780000)>>19;
    int32_t Rn = (instrut & 0x00078000)>>15;
    int32_t Rm = (instrut & 0x00007800)>>11;
    int32_t addr = (instrut & 0x0000ffff);
    int32_t flag = (instrut & 0x00000700)>>8;
    int8_t immediate = (instrut & 0x000000ff);
    switch (opcode)
    {
        case 1: // ADD
            result->inst.instruction_operator = 1;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            result->inst.operands[2] = Rm;
            registe->add(Rd);
            cout<<"The command is ADD R"<<Rd<<" R"<<Rn<<" R"<<Rm<<endl;
            result->ins_text = "ADD R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm);
            break;
        case 2: //ADDI
            result->inst.instruction_operator = 2;
            result->inst.operands[0] = Rd;
            result->inst.address = immediate;
            registe->add(Rd);
            cout<<"The command is ADDI R"<<Rd<<" "<<immediate<<endl;
            result->ins_text = "ADDI R"+to_string(Rd)+" "+to_string(immediate);
            break;
        case 4:  //SUB
            result->inst.instruction_operator = 4;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            result->inst.operands[2] = Rm;
            registe->add(Rd);
            cout<<"The command is SUB R"<<Rd<<" R"<<Rn<<" R"<<Rm<<endl;
            result->ins_text = "SUB R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm);
            break;
        case 5: //SUBI
            result->inst.instruction_operator = 5;
            result->inst.operands[0] = Rd;
            result->inst.address = immediate;
            registe->add(Rd);
            cout<<"The command is SUBI R"<<Rd<<" "<<immediate<<endl;
            result->ins_text = "SUBI R"+to_string(Rd)+" "+to_string(immediate);
            break;
        case 7:  //MUL
            result->inst.instruction_operator = 7;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            result->inst.operands[2] = Rm;
            registe->add(Rd);
            cout<<"The command is MUL R"<<Rd<<" R"<<Rn<<" R"<<Rm<<endl;
            result->ins_text = "MUL R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm);
            break;
        case 10: //LOAD
            result->inst.instruction_operator = 10;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            registe->add(Rd);
            //cout<<"The command is "LOAD R"<<to_string(Rd)<<" R"<<to_string(Rn)<<endl;
            result->ins_text = "LOAD R"+to_string(Rd)+" R"+to_string(Rn);
            break; 
        case 11: //LOADI
            result->inst.instruction_operator = 11;
            result->inst.operands[0] = Rd;
            result->inst.address = addr;
            registe->add(Rd);
            //cout<<"The command is LOADI R"<<Rd<<" "<<addr<<" "<<endl;
            result->ins_text = "LOADI R"+to_string(Rd)+" "+to_string(addr);
            break;
        case 13://STORE
            result->inst.instruction_operator = 13;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            registe->add(Rd);
            //cout<<"The command is "LOAD R"<<to_string(Rd)<<" R"<<to_string(Rn)<<endl;
            result->ins_text = "STORE R"+to_string(Rd)+" R"+to_string(Rn);
            break;
        case 14: //STOREI
            result->inst.instruction_operator = 14;
            result->inst.operands[0] = Rd;
            result->inst.address = addr;
            cout<<"The command is STOREI R"<<Rd<<" "<<addr<<" "<<endl;
            result->ins_text = "STOREI R"+to_string(Rd)+" "+to_string(addr)+" ";
            break;
        case 16://AND
            result->inst.instruction_operator = 16;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            result->inst.operands[2] = Rm;
            registe->add(Rd);
            cout<<"The command is AND R"<<Rd<<" R"<<Rn<<" R"<<Rm<<endl;
            result->ins_text = "AND R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm);
            break;
        case 17://OR
            result->inst.instruction_operator = 17;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            result->inst.operands[2] = Rm;
            registe->add(Rd);
            cout<<"The command is OR R"<<Rd<<" R"<<Rn<<" R"<<Rm<<endl;
            result->ins_text = "OR R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm);
            break;
        case 18://NOT
            result->inst.instruction_operator = 18;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            registe->add(Rd);
            cout<<"The command is NOT R"<<Rd<<" R"<<Rn<<" R"<<Rm<<endl;
            result->ins_text = "NOT R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm);
            break;
        case 19://XOR
            result->inst.instruction_operator = 19;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            result->inst.operands[2] = Rm;
            registe->add(Rd);
            cout<<"The command is XOR R"<<Rd<<" R"<<Rn<<" R"<<Rm<<endl;
            result->ins_text = "XOR R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm);
            break;
        case 20: //Branch
            result->inst.instruction_operator = 20;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rn;
            result->inst.operands[2] = Rm;
            result->inst.address = 0 + immediate;
            result->inst.cmp = flag;
            cout<<"The command is Branch R"<<Rd<<" R"<<Rn<<" R"<<Rm<<" "<<flag<<" "<<immediate<<endl;
            result->ins_text = "Branch R"+to_string(Rd)+" R"+to_string(Rn)+" R"+to_string(Rm)+" "+to_string(flag)+" "+to_string(result->inst.address);
            break;
        case 21://JUMP
            result->inst.instruction_operator = 21;
            result->inst.operands[0] = Rd;
            result->inst.address = addr;
            cout<<"The command is JUMP R"<<Rd<<" "<<addr<<" "<<endl;
            result->ins_text = "JUMP R"+to_string(Rd)+" "+to_string(addr)+" ";
            break;
        case 31://HALT
            result->inst.instruction_operator = 31;
            cout<<"The command is HALT";
            result->ins_text = "HALT";
            break;
        default:
            result->inst.instruction_operator = -1;
            result->inst.operands[0] = -1;
            result->inst.operands[1] = -1;
            result->inst.operands[2] = -1;
            cout<<"The command is None"<<endl;
            result->ins_text = "None ";
            break;

    };

    decode_queue.pop();
    return result;
}

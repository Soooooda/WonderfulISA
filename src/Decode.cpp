# include "../include/Decode.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
Decode::Decode()
{

}

output* Decode::execute()
{
    if(decode_queue.empty())
    {
        cout<<"decode skip"<<endl;
        return NULL;
    }
    output* result = (struct output *) malloc(sizeof(output));
    int32_t instrut = decode_queue.front();
    int32_t opcode = (instrut & 0xfc000000)>>26;
    int32_t Rd = (instrut & 0x00780000)>>19;
    int32_t Rn = (instrut & 0x00078000)>>15;
    int32_t Rm = (instrut & 0x00007800)>>11;
    int32_t addr = (instrut & 0x0000ffff);
    switch (opcode)
    {
        case 1: // ADD
            result->inst.instruction_operator = 3;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rm;
            result->inst.operands[2] = Rn;
            cout<<"The command is ADD "<<Rd<<" "<<Rm<<" "<<Rn<<endl;
            break;
        case 4:  //SUB
            result->inst.instruction_operator = 4;
            result->inst.operands[0] = Rd;
            result->inst.operands[1] = Rm;
            result->inst.operands[2] = Rn;
            cout<<"The command is SUB "<<Rd<<" "<<Rm<<" "<<Rn<<endl;
            break;
        case 11: //LOAD
            result->inst.instruction_operator = 1;
            result->inst.operands[0] = Rd;
            result->inst.address = addr;
            cout<<"The command is STOREI "<<Rd<<" "<<addr<<" "<<endl;
            break;
        case 14: //STORE
            result->inst.instruction_operator = 2;
            result->inst.operands[0] = Rd;
            result->inst.address = addr;
            cout<<"The command is STOREI "<<Rd<<" "<<addr<<" "<<endl;
            break;
        case 21://JUMP
            result->inst.instruction_operator = 5;
            result->inst.operands[0] = Rd;
            result->inst.address = addr;
        default:
            result->inst.instruction_operator = -1;
            result->inst.operands[0] = -1;
            result->inst.operands[1] = -1;
            result->inst.operands[2] = -1;
            cout<<"The command is None"<<endl;
            break;
    };

    decode_queue.pop();
    return result;
}

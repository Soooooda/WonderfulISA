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
    string instrut = decode_queue.front();
    istringstream iss(instrut);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(tokens));
    cout<<"result opt: "<<tokens[0]<<endl;

//    char* s = "ds";
    if(tokens[0]=="LOAD")
    {
        result->inst.instruction_operator = 1;
    }
    else if(tokens[0]=="STORE")
    {
        cout<<"!!!!store"<<endl;
        result->inst.instruction_operator = 2;
    }
    else if(tokens[0]=="ADD")
    {
        result->inst.instruction_operator = 3;
    }
    else if(tokens[0]=="MINUS")
    {
        result->inst.instruction_operator = 4;
    }
    result->inst.operands[0] = stoi(tokens[1]);
    result->inst.operands[1] = stoi(tokens[2]);
    result->inst.operands[2] = stoi(tokens[3]);
    result->inst.address = stoi(tokens[4]);
    result->inst.cmp = stoi(tokens[5]);
    result->pc = stoi(tokens[6]);
    decode_queue.pop();
    return result;
}

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

output *Decode::execute()
{
    if(decode_queue.empty())
    {
        return NULL;
    }
    string instru = decode_queue.front();
    //string sentence = "And I feel fine...";
    istringstream iss(instru);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(tokens));

    output *result = (struct output *)malloc(sizeof(output));
    int16_t count = 0;
    for(string token: tokens){

        if(count==0)
        {
            result->inst.instruction_operator = tokens[0].c_str();
            cout<<"token:"<<token.c_str()<<endl;
        }
        else if(count == 1)
        {
            result->inst.operands[0] = stoi(tokens[1].c_str());
        }
        else if(count== 2)
        {
            result->inst.operands[1] = stoi(tokens[2].c_str());
        }
        else if(count==3)
        {
            result->inst.operands[2] = stoi(tokens[3].c_str());
        }
        else if(count == 4)
        {
            result->inst.address = stoi(tokens[4].c_str());
        }
        else if(count==5)
        {
            result->inst.cmp = stoi(tokens[5].c_str());
        }

        count+=1;
    }
    decode_queue.pop();
//
    return result;
//    result.opera
}

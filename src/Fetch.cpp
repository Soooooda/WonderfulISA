# include "../include/Fetch.h"

Fetch::Fetch()
{

}

string Fetch::execute(string *instruction)
{
    if(fetch_queue.empty())
    {
        return "";
    }
    int16_t pc = fetch_queue.front();
    fetch_queue.pop();

    return instruction[pc];
}

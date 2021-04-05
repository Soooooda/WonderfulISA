# include "../include/Fetch.h"

Fetch::Fetch()
{
    clear(fetch_queue);
}

string Fetch::execute(string *instruction, Simulator *simulator)
{
    if(fetch_queue.empty())
    {
        cout<<"fetch skip"<<endl;
        return "";
    }
    int16_t pc = fetch_queue.front();
    cout<<"pc:"<<pc<<endl;
    fetch_queue.pop();

    return instruction[pc]+" "+to_string(pc);
}

# include "../include/Fetch.h"

Fetch::Fetch()
{

}

string Fetch::execute(string *instruction)
{
    if(fetch_queue.empty())
    {
        cout<<"fetch skip"<<endl;
        return "";
    }
    int16_t pc = fetch_queue.front();
    cout<<"pc:"<<pc<<endl;
    fetch_queue.pop();

    return instruction[pc];
}

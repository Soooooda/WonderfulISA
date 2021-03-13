// A memory is an array of binary values
// Takes address, and has commands for read/write Read returns data, write saves data
// Has an access time
// May also return a bounds error
// A cache has a pointer to a lower level memory
// Can write one class, and instantiate each level, giving the constructor its parameters and a pointer to the level below

#include "cache.hpp"
using namespace std;
class Simulator
{
    public:
        int *memory;
        Cache l1_cache;
        Cache l2_cache;
        Simulator();
        void instantiate();
};

Simulator::Simulator()
{
    memory = (int*) malloc(sizeof(int) * 512*1024*1024);
    cout<<"constructed!"<<endl;
}

void Simulator::instantiate()
{
    l1_cache = Cache(16,16*23,1,NULL);
    cout<<"instantiate succees!"<<endl;
}


int main()
{
    // cout<<"enter"<<endl;
    Simulator simulator;
    simulator.instantiate();
    int a = 5;
    // cout<<"hello"<<endl;
    return 0;
}

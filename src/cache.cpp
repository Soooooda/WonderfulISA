#include "cache.hpp"
using namespace std;

// 构造函数
Cache::Cache()
{

}

Cache::Cache(int length, int size, int delay, int time, int count, Cache *next)
{
    time_cycle = time;
    cache_count = count;
    line_length = length;
    cache_size = size;
    cache_delay = delay;
    next_level = next;
    cache = (bool*)malloc(sizeof(bool) * cache_size);
    cout << "Cache instantiated" << endl;
}

int Cache::getNextLevelLineLength()
{
    return next_level->line_length;
}

//For read, also return line
string Cache::read(int address)
{
    while (cache_count != 0)
    {
        cout <<"wait";
        cache_delay = 0;

    }
    
    cout << "wait" << endl;
    
    return "done";
}

//for write, store the line into the memory array
string Cache::write(int address, int value)
{
    cout << "wait" << endl;
    cache_delay+=3;
    cout << "done! the line is stored" << endl;
    return "done";
}



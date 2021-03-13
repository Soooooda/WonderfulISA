#include "cache.hpp"
using namespace std;
// 构造函数
Cache::Cache()
{

}

Cache::Cache(int length, int size, int delay, Cache *next)
{
    line_length = length;
    cache_size = size;
    cache_delay = delay;
    next_level = next;
    cout << "Cache instantiated" << endl;
}

int Cache::getNextLevelLineLength()
{
    return next_level->line_length;
}

//For read, also return line
string Cache::read(int address)
{
    cout << "wait" << endl;
    
    return "done";
}

//for write, store the line into the memory array
string Cache::write(int address)
{
    cout << "wait" << endl;
    cout << "done! the line is stored" << endl;
    return "done";
}



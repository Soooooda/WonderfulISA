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
    int temp_cache[size][5];
    cache = (bool*)malloc(sizeof(bool) * cache_size);
    cout << "Cache instantiated" << endl;
}

int Cache::getNextLevelLineLength()
{
    return next_level->line_length;
}

//For read, also return line
int Cache::read(int address)
{
    cout << "wait" << endl;
    while (cache_count != 0)
    {
        cout <<"wait Time Cycle: "<< time_cycle << endl;
        time_cycle += 1;

    }
    
    int line_number = address/4;
    int index = address%16;
    int offset = address%4;
    if(temp_cache[index][5] == line_number){
        return temp_cache[index][offset];
    }
    else{
        //TODO load from memory
        time_cycle +=3;
        return -1;

    }
}

//for write, store the line into the memory array
string Cache::write(int address, int value)
{
    cout << "wait" << endl;
        while (cache_count != 0)
    {
        cout <<"wait Time Cycle: "<< time_cycle << endl;
        time_cycle += 1;

    }
    int line_number = address/4;
    int index = address%16;
    int offset = address%4;
    if(temp_cache[index][5] == line_number){
        temp_cache[index][offset] = value; //store value in cache
        temp_cache[index][4] = 1;    //set validbit to 1
        temp_cache[index][5] = 1;    //set dirty bit to 1
    }
    else{
        time_cycle += 3;
        if (temp_cache[index][4] == 0){
            //TODO load 整条memory
            temp_cache[index][offset] = value; //store value in cache
            temp_cache[index][4] = 1;    //set validbit to 1
            temp_cache[index][3] = 1;    //set dirty bit to 1
        }
        else{
            if (temp_cache[index][3] ==0){
                //TODO load 整条memory
                temp_cache[index][offset] = value; //store value in cache
                temp_cache[index][4] = 1;    //set validbit to 1
                temp_cache[index][3] = 1;    //set dirty bit to 1
            }
            else{
                //TODO write back to memory
                //TODO load 整条memory
                temp_cache[index][offset] = value; //store value in cache
                temp_cache[index][4] = 1;    //set validbit to 1
                temp_cache[index][3] = 1;    //set dirty bit to 1
            }
        }
    }
    cache_delay+=3;
    cout << "done! the line is stored" << endl;
    return "done";
}



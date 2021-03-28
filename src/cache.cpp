#include "../include/cache.hpp"
#include <bitset>
using namespace std;

// 构造函数
Cache::Cache()
{

}

Cache::Cache(int16_t length, int16_t size, int16_t delay, int16_t time, int16_t count, Cache *next)
{
    time_cycle = time;
    cache_count = count;
    line_length = length;
    cache_size = size;
    cache_delay = delay;
    next_level = next;
    cache = (CacheLine*) malloc(sizeof(CacheLine) * cache_size);
    memset(cache, 0, sizeof(CacheLine) * cache_size);
    for(int16_t ptr = 0; ptr<cache_size;ptr+=1)
    {
        cache[ptr].lru = ptr;
    }
    cout << "Cache instantiated" << endl;
}

int16_t Cache::getNextLevelLineLength()
{
    return next_level->line_length;
}

void Cache::adjust_LRU(int16_t line)
{
    int16_t current_lru = cache[line].lru;
    for(int16_t ptr = 0; ptr<cache_size;ptr+=1)
    {
        if(cache[ptr].lru<current_lru)
        {
            cache[ptr].lru+=1;
        }
    }
    cache[line].lru = 0;
}

//if hit, return ptr
//else return -1
int16_t Cache::request_cache(int16_t address)
{

    int16_t blockAddress = address>>TAG_INDEX_OFFSET;
    int16_t ptr = blockAddress % cache_size;
    cout<<"ptr:"<<ptr<<endl;
    //calculate if the address is in the cache
    if(cache[ptr].header>>TAG_INDEX_OFFSET == blockAddress){
        //return ptr;
        int16_t valid_flag = cache[ptr].header & VALID_FLAG;
        if(valid_flag!=0)
        {
            return ptr;
        }
        else
        {
            return -1;
        }
    }
    return -1;

}

void Cache::set_dirty(int16_t line, int16_t flag)
{
    cache[line].header = (cache[line].header & ~(1UL << 1)) | (flag << 1);
    //cache[line].header ^= (-(unsigned long)flag ^ cache[line].header) & (1UL << 1);
}

void Cache::set_valid(int16_t line, int16_t flag)
{
    cache[line].header = (cache[line].header & ~(1UL)) | (flag);
    //cache[line].header ^= (-(unsigned long)flag ^ cache[line].header) & (1UL);
}

bool Cache::write_from_memory(int16_t address, int16_t line, int16_t* block)
{
    //modify LRU
    adjust_LRU(line);

    //modify tag+index
    cache[line].header = address&TAG_INDEX_FLAG;

    //set valid
    set_valid(line, 1);

    //assign value to cache line
    cache[line].offset[0] = block[0];
    cache[line].offset[1] = block[1];
    cache[line].offset[2] = block[2];
    cache[line].offset[3] = block[3];
    return true;
}

void Cache::write_value(int16_t line, int16_t offset, int16_t value)
{
    cache[line].offset[offset] = value;
}


//find a line to evict
int16_t Cache::evict_line(int16_t address)
{
    int16_t blockAddress = address>>TAG_INDEX_OFFSET;
    int16_t ptr = blockAddress % cache_size;
    return ptr;

}

bool Cache::is_dirty(int16_t line)
{
    int16_t dirty = cache[line].header & DIRTY_FLAG;
    if(dirty==0)
    {
        return false;
    }
    return true;
}

int16_t Cache::get_start_address(int16_t line)
{
    return cache[line].header&TAG_INDEX_FLAG;
}

int16_t* Cache::get_block(int16_t line)
{
    return cache[line].offset;
}

void Cache::view()
{
    printf("===============LRU status===============\n");
    for(int16_t ptr = 0; ptr<cache_size;ptr+=1)
    {
        printf("header: 0x%04X valid: %2d dirty: %2d values: %10d %10d %10d %10d lru: %10d\n",cache[ptr].header&TAG_INDEX_FLAG, cache[ptr].header&VALID_FLAG, (cache[ptr].header&DIRTY_FLAG)>>1, cache[ptr].offset[0],cache[ptr].offset[1],cache[ptr].offset[2],cache[ptr].offset[3],cache[ptr].lru);
    }
    printf("===============LRU status===============\n\n");
}


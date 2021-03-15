#include "../include/cache.hpp"
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
    int16_t temp_cache[size][5]; // 这5个值分别是什么？
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

int16_t Cache::request_cache(int16_t address)
{
    int16_t tag_index = address & TAG_INDEX_FLAG;

    for(int16_t ptr = 0; ptr<cache_size;ptr+=1)
    {
        int16_t header = cache[ptr].header;
        int16_t valid_flag = header & VALID_FLAG;
        int16_t ptr_tag_index = header & TAG_INDEX_FLAG;
        if(ptr_tag_index == tag_index){
            if(valid_flag!=0)
            {
                return ptr;
            }
            else
            {
                return -1;
            }
        }
    }
    return -1;
}

void Cache::set_dirty(int16_t line, int16_t flag)
{
    cache[line].header ^= (-flag ^ cache[line].header) & (1UL << 1);
}

void Cache::set_valid(int16_t line, int16_t flag)
{
    cache[line].header ^= (-flag ^ cache[line].header) & (1UL);
}

bool Cache::write_from_memory(int16_t address, int16_t line, int16_t* block)
{
    //save dirty flag
    int16_t dirty = 0;
    if((cache[line].header|DIRTY_FLAG)!=0)
    {
        dirty = 1;
    }

    //modify valid flag
    // cache[line].header = cache[line].header|VALID_FLAG;

    //modify LRU
    adjust_LRU(line);

    //modify tag+index
    cache[line].header = address&TAG_INDEX_FLAG;

    //set valid
    set_valid(line, 1);

    //set dirty
    set_valid(line, dirty);

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


int16_t Cache::find_line()
{
    for(int16_t ptr = 0; ptr<cache_size;ptr+=1)
    {
        int16_t header = cache[ptr].header;
        int16_t valid_flag = header & VALID_FLAG;
        if(valid_flag==0)
        {
            return ptr;
        }
    }
    
    for(int16_t ptr = 0; ptr<cache_size;ptr+=1)
    {
        int16_t ptr_lru = cache[ptr].lru;
        if(ptr_lru==cache_size-1)
        {
            return ptr;
        }
    }
    return -1;
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


//For read, also return line
int16_t Cache::read(int16_t address)
{
    cout << "wait" << endl;
    while (cache_count != 0)
    {
        cout <<"wait Time Cycle: "<< time_cycle << endl;
        time_cycle += 1;

    }
    
    int16_t line_number = address/4;
    int16_t index = address%16;
    int16_t offset = address%4;
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
string Cache::write(int16_t address, int16_t value)
{
    cout << "wait" << endl;
        while (cache_count != 0)
    {
        cout <<"wait Time Cycle: "<< time_cycle << endl;
        time_cycle += 1;

    }
    int16_t line_number = address/4;
    int16_t index = address%16;
    int16_t offset = address%4;
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



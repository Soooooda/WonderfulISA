#ifndef CACHE_HPP
#define CACHE_HPP
#include <iostream>
#include <cstring>

using namespace std;
#define TAG_INDEX_FLAG ((1<<16)-4)
#define TAG_INDEX_OFFSET 2
#define DIRTY_FLAG (1<<1)
#define VALID_FLAG 1
#define BLOCK_SIZE 16*4
// Instantiate DRAM level with constructor having default of no lower level 
// Has line length, size (data array dimensions), delay
// Instantiate cache level with size, delay, pointer to level below 
// Get line length from level below, using getter method
// Both support line length read and write with delay 
// Additional API for giving UI direct access to contents
// tag index dirty valid o                           lru
// 4   10     1     1     16     16      16      16  16
struct CacheLine
{
    // header : tag(4) + index(10) + dirty(1) + valid(1)
    int16_t header;
    int16_t offset[4];
    int16_t lru;
};

class Cache
{
    public:
        Cache();
        Cache(int16_t length, int16_t size, int16_t delay, int16_t time, int16_t count, Cache *next);  // 这是构造函数
        bool setLineLength(int16_t length);  // 成员函数声明
        int16_t getNextLevelLineLength();
        int16_t read(int16_t address);
        string write(int16_t address, int16_t value);
        void view();
        int16_t request_cache(int16_t address);
        bool write_from_memory(int16_t address, int16_t line, int16_t* block);
        int16_t evict_line(int16_t address);
        void adjust_LRU(int16_t line);
        bool is_dirty(int16_t line);
        int16_t get_start_address(int16_t line);
        int16_t* get_block(int16_t line);
        void set_dirty(int16_t line, int16_t flag);
        void set_valid(int16_t line, int16_t flag);
        void write_value(int16_t line, int16_t offset, int16_t value);
        CacheLine* cache; //缓存
    
    private:
        int16_t line_length;   // line长度
        int16_t cache_size;  // 缓存大小
        int16_t cache_delay;   // 延迟
        int16_t cache_count;    //命令统计
        int16_t time_cycle;     //时间统计

        Cache *next_level;
};
#endif

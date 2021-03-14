#include <iostream>
using namespace std;
#define TAG_OFFSET 0
#define INDEX_OFFSET 2
#define DIRTY_OFFSET 5
#define VALID_OFFSET 6
#define FIRST_OFFSET 7
#define SECOND_OFFSET 15
// Instantiate DRAM level with constructor having default of no lower level 
// Has line length, size (data array dimensions), delay
// Instantiate cache level with size, delay, pointer to level below 
// Get line length from level below, using getter method
// Both support line length read and write with delay 
// Additional API for giving UI direct access to contents
// tag index dirty valid offset0 offset1
// 2   3     1     1     8       8
class Cache
{
    public:
        Cache();
        Cache(int length, int size, int delay, int time, int count, Cache *next);  // 这是构造函数
        bool setLineLength(int length);  // 成员函数声明
        int getNextLevelLineLength();
        int read(int address);
        string write(int address, int value);
        void view();
    
    private:
        int line_length;   // line长度
        int cache_size;  // 缓存大小
        int cache_delay;   // 延迟
        int cache_count;    //命令统计
        int time_cycle;     //时间统计
        int temp_cache[16][5];  //caches试行
        bool *cache; //缓存
        Cache *next_level;
};
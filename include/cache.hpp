#include <iostream>
using namespace std;
// Instantiate DRAM level with constructor having default of no lower level 
// Has line length, size (data array dimensions), delay
// Instantiate cache level with size, delay, pointer to level below 
// Get line length from level below, using getter method
// Both support line length read and write with delay 
// Additional API for giving UI direct access to contents
class Cache
{
    public:
        Cache();
        Cache(int length, int size, int delay, Cache *next);  // 这是构造函数
        bool setLineLength(int length);  // 成员函数声明
        int getNextLevelLineLength();
        string read(int address);
        string write(int address);
        void view();
    
    private:
        int line_length;   // line长度
        int cache_size;  // 缓存大小
        int cache_delay;   // 延迟
        Cache *next_level;
};
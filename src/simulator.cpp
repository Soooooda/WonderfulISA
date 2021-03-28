// A memory is an array of binary values
// Takes address, and has commands for read/write Read returns data, write saves data
// Has an access time
// May also return a bounds error
// A cache has a pointer to a lower level memory
// Can write one class, and instantiate each level, giving the constructor its parameters and a pointer to the level below
#include "../include/simulator.hpp"
Simulator::Simulator()
{
    
}

void Simulator::instantiate()
{
    // l1_cache = Cache(16,16*23,1,NULL);
    //memory大小为2^16*int16
    memory = (int16_t*) malloc(sizeof(int16_t) *1024*64);
    memset(memory, 0, sizeof(int16_t) *1024*64);
    cout<<"memory constructed!"<<endl;

    l1_cache = Cache(16*4, 16, 1, 2, 3, NULL);
    cout<<"l1 cache constructed!"<<endl;

}

string Simulator::write_memory(int16_t address, int16_t value)
{
    // *(memory+address) = value;
    // printf("memory address written: %p, value: %d\n", address, *(memory+address));
    int16_t cache_line = l1_cache.request_cache(address);

    //cache miss
    if(cache_line==-1)
    {
        cout<<"write miss"<<endl;
        cache_line = l1_cache.evict_line(address);
        cout<<"find line: "<<cache_line<<endl;
        if(l1_cache.is_dirty(cache_line))
        {
            cout<<"dirty"<<endl;
            int16_t dirty_address = l1_cache.get_start_address(cache_line);
            int16_t* dirty_block = l1_cache.get_block(cache_line);

            //写回内存
            memory[dirty_address] =  dirty_block[0];
            memory[dirty_address+1] =  dirty_block[1];
            memory[dirty_address+2] =  dirty_block[2];
            memory[dirty_address+3] =  dirty_block[3];
        }
        else
        {
            cout<<"not dirty"<<endl;
        }
        //write cache
        l1_cache.write_from_memory(address, cache_line, memory+(address&BLOCK_OFFSET));
        l1_cache.set_dirty(cache_line, 1);
    }
    else
    {
        cout<<"write hit"<<endl;
    }

    //set dirty
    l1_cache.set_dirty(cache_line, 1);

    
    // l1_cache.write_value(cache_line, address, value)
    l1_cache.write_value(cache_line, address&ADDRESS_OFFSET, value);
    l1_cache.view();
    return "ok";
}


int16_t Simulator::read_memory(int16_t address)
{
    // printf("memory address read: %p, value: %d\n", address, *(memory+address));
    // l1_cache.read(address);
    int16_t cache_line = l1_cache.request_cache(address);
    if(cache_line==-1)
    {
        cout<<"read miss"<<endl;
        cache_line = l1_cache.evict_line(address);
        cout<<"find line: "<<cache_line<<endl;
        if(l1_cache.is_dirty(cache_line))
        {
            int16_t dirty_address = l1_cache.get_start_address(cache_line);
            int16_t* dirty_block = l1_cache.get_block(cache_line);
            //写回内存
            memory[dirty_address] =  dirty_block[0];
            memory[dirty_address+1] =  dirty_block[1];
            memory[dirty_address+2] =  dirty_block[2];
            memory[dirty_address+3] =  dirty_block[3];
        }
        //set dirty
        l1_cache.set_dirty(cache_line, 0);

        //write cache
        l1_cache.write_from_memory(address, cache_line, memory+(address&BLOCK_OFFSET));
    }
    else
    {
        cout<<"read hit"<<endl;
    }

    //return value
    int16_t* block = l1_cache.get_block(cache_line);
    int16_t offset = address&ADDRESS_OFFSET;
    cout<<block[offset]<<endl;
    l1_cache.view();
    return block[offset];
}

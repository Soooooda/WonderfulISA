# include "../include/Stage.h"

//     queue<int16_t> instruction_queue;
//     int16_t cost_time;
Stage::Stage()
{

}

void Stage::clear( std::queue<int16_t> &q )
{
   std::queue<int16_t> empty;
   std::swap( q, empty );
}


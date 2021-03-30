# include "../include/WriteBack.h"

WriteBack::WriteBack()
{

}

void WriteBack::execute()
{
    output *data = (struct output*)wb_queue.front();

    free(data);
    wb_queue.pop();
    return;
}

# include "../include/Execute.h"

Execute::Execute()
{

}

output *Execute::execute(Register* registe)
{
    if(execute_queue.empty())
    {
        cout<<"execute skip"<<endl;
        return NULL;
    }

    output *data = (struct output *)execute_queue.front();
    cout<<"alu opt:"<<data->inst.instruction_operator<<endl;

    if (data->inst.instruction_operator == 3) {
        data->value = registe->get(data->inst.operands[1]) + registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        registe->set(data->register_id, data->value);
        cout<<"add:"<<data->value<<endl;
    } else if (data->inst.instruction_operator == 4)
    {
        data->value = registe->get(data->inst.operands[1]) - registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        registe->set(data->register_id, data->value);
        cout<<"minus:"<<data->value<<endl;
    }

    return data;
}

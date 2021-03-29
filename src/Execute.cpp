# include "../include/Execute.h"

Execute::Execute()
{

}

output *Execute::execute(Register registe)
{
    if(execute_queue.empty())
    {
        return NULL;
    }
    output *data = execute_queue.front();
    cout<<"here: "<<data->inst.instruction_operator<<endl;
    if (data->inst.instruction_operator == "ADD") {
        data->value = registe.get(data->inst.operands[1]) + registe.get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        registe.set(data->register_id, data->value);
        cout<<"add:"<<data->value<<endl;
    } else if (data->inst.instruction_operator == "MINUS")
    {
        data->value = registe.get(data->inst.operands[1]) - registe.get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        registe.set(data->register_id, data->value);
        cout<<data->value<<endl;
    }

    execute_queue.pop();
    return data;
}

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

    if (data->inst.instruction_operator == 1) {//add
        data->value = registe->get(data->inst.operands[1]) + registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"add:"<<data->value<<endl;
    } 
    else if (data->inst.instruction_operator == 2)
    {//ADDI
        data->value = registe->get(data->inst.operands[1]) + data->inst.address;
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"addI:"<<data->value<<endl;
    }
    else if (data->inst.instruction_operator == 4)
    {//minus
        data->value = registe->get(data->inst.operands[1]) - registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"minus:"<<data->value<<endl;
    } 
    else if (data->inst.instruction_operator == 5)
    {//minI
        data->value = registe->get(data->inst.operands[1]) - data->inst.address;
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"minusI:"<<data->value<<endl;
    }
    else if (data->inst.instruction_operator == 7)
    {//mul
        data->value = registe->get(data->inst.operands[1]) * registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"mul:"<<data->value<<endl;
    }
    else if (data->inst.instruction_operator == 16)
    {//AND
        data->value = registe->get(data->inst.operands[1]) & registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"minus:"<<data->value<<endl;
    }
    else if (data->inst.instruction_operator == 17)
    {//OR
        data->value = registe->get(data->inst.operands[1]) | registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"minus:"<<data->value<<endl;
    }
    else if (data->inst.instruction_operator == 18)
    {//NOT
        data->value = ~(registe->get(data->inst.operands[1]));
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"minus:"<<data->value<<endl;
    }
    else if (data->inst.instruction_operator == 19)
    {//XOR
        data->value = registe->get(data->inst.operands[1]) ^ registe->get(data->inst.operands[2]);
        data->register_id = data->inst.operands[0];
        //registe->set(data->register_id, data->value);
        cout<<"minus:"<<data->value<<endl;
    }
    return data;
}

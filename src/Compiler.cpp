# include "../include/Compiler.h"
//#define OPCODE_OFFSET 26
//#define RD_OFFSET 19
//#define RN_OFFSET 15
//#define RM_OFFSET 11
//#define IMMEDIATE_OFFSET 0
//#define ADD 1<<OPCODE_OFFSET
//#define SUB 4<<OPCODE_OFFSET
//#define LOADI 11<<OPCODE_OFFSET
//#define BRANCH 20<<OPCODE_OFFSET
//#define STOREI 14<<OPCODE_OFFSET
//#define HALT 31<<OPCODE_OFFSET


Compiler::Compiler()
{

}

int32_t Compiler::proccess_add(vector<string> tokens)
{
    int32_t code = 0;
    if(tokens[0]=="ADD")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t rm = stoi(tokens[3].erase(0, 1));
        code = code | ADD | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (rm<<RM_OFFSET);
    }
    if(tokens[0]=="ADDI")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t immediate = stoi(tokens[3].erase(0, 1));
        code = code | ADDI | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (immediate<<IMMEDIATE_OFFSET);
    }
    return code;
}

int32_t Compiler::proccess_sub(vector<string> tokens)
{
    int32_t code = 0;
    if(tokens[0]=="SUB")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t rm = stoi(tokens[3].erase(0, 1));
        code = code | SUB | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (rm<<RM_OFFSET);
    }
    if(tokens[0]=="SUBI")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t immediate = stoi(tokens[3].erase(0, 1));
        code = code | SUBI | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (immediate<<IMMEDIATE_OFFSET);
    }
    return code;
}

int32_t Compiler::proccess_load(vector<string> tokens)
{
    int32_t code = 0;
    if(tokens[0]=="LOADI")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t immediate = stoi(tokens[2]);
        code = code | LOADI | (rd<<RD_OFFSET) | (immediate<<IMMEDIATE_OFFSET);
    }
    return code;
}

int32_t Compiler::proccess_branch(vector<string> tokens)
{
    int32_t code = 0;
    int32_t rd = stoi(tokens[1].erase(0, 1));
    int32_t rn = stoi(tokens[2].erase(0, 1));
    int32_t rm = stoi(tokens[3].erase(0, 1));
    int32_t branch_flag = stoi(tokens[4]);
    int32_t immediate = stoi(tokens[5]);
    code = code | BRANCH | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (rm<<RM_OFFSET) | (branch_flag<<BRANCH_FLAG_OFFSET) | (immediate<<IMMEDIATE_OFFSET);
    return code;
}

int32_t Compiler::proccess_halt(vector<string> tokens)
{
    int32_t code = HALT;
    return code;
}

int32_t Compiler::proccess_store(vector<string> tokens)
{
    int32_t code = 0;
    if(tokens[0]=="STOREI")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t immediate = stoi(tokens[2]);
        code = code | STOREI | (rd<<RD_OFFSET) | (immediate<<IMMEDIATE_OFFSET);
    }
    return code;
}
int32_t Compiler::proccess_bit(vector<string> tokens)
{
    int32_t code = 0;
    if(tokens[0]=="AND")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t rm = stoi(tokens[3].erase(0, 1));
        code = code | AND | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (rm<<RM_OFFSET);
    }
    if(tokens[0]=="OR")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t rm = stoi(tokens[3].erase(0, 1));
        code = code | OR | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (rm<<RM_OFFSET);
    }
    if(tokens[0]=="NOT")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t rm = stoi(tokens[3].erase(0, 1));
        code = code | NOT | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (rm<<RM_OFFSET);
    }
    if(tokens[0]=="XOR")
    {
        int32_t rd = stoi(tokens[1].erase(0, 1));
        int32_t rn = stoi(tokens[2].erase(0, 1));
        int32_t rm = stoi(tokens[3].erase(0, 1));
        code = code | XOR | (rd<<RD_OFFSET) | (rn<<RN_OFFSET) | (rm<<RM_OFFSET);
    }
}
        // from assembly to machine code
int32_t Compiler::get_machine_code(string assembly)
{
    istringstream iss(assembly);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(tokens));
    string opcode = tokens[0];
    if(opcode=="ADD" || opcode=="ADDI")
        return proccess_add(tokens);
    if(opcode=="SUB")
        return proccess_sub(tokens);
    if(opcode=="LOAD" || opcode=="LOADI")
        return proccess_load(tokens);
    if(opcode=="BRANCH")
        return proccess_branch(tokens);
    if(opcode=="STORE" || opcode=="STOREI")
        return proccess_store(tokens);
    if(opcode=="HALT")
        return proccess_halt(tokens);
    if(opcode =="AND"||opcode =="OR"||opcode =="NOT"||opcode =="XOR")
        return proccess_bit(tokens);
    return -1;
}


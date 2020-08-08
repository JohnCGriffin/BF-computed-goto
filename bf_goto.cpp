
#include "bf_instruction.hpp"

#include <map>
#include <sstream>

namespace bf {

    static void verify_address_table_completeness(const std::map<Action,void*>&);

    void execute(std::vector<Instruction>&  _instructions)
    {
        std::map<Action,void*> addrs;

        // Note that initialization in modern manner chokes clang/g++ 
        // when in c++14/17.  Direct assignment one by one seems to work.
        addrs[MOVE]        = &&_MOVE;
        addrs[INCR]        = &&_INCR;
        addrs[TRUEJUMP]    = &&_TRUEJUMP;
        addrs[FALSEJUMP]   = &&_FALSEJUMP;
        addrs[ZERO]        = &&_ZERO;
        addrs[PRINT]       = &&_PRINT;
        addrs[READ]        = &&_READ;
        addrs[TERMINATE]   = &&_TERMINATE;

	verify_address_table_completeness(addrs);

        for(auto& instr : _instructions){
            instr.jump = addrs.at(instr.action);
        }

        std::vector<char> characters(30000);
        char* ptr = characters.data();
        auto IP = _instructions.data();

        // initial JUMP.  The remainder are executed via LOOP macro.
        goto *(IP->jump);

#define LOOP() IP++; goto *(IP->jump)//*jumps[IP->action]

    _TRUEJUMP:
        if(*ptr){
            IP += IP->val;
        }
        LOOP();
        
    _FALSEJUMP:     
        if(!(*ptr)){
            IP += IP->val;
        }
        LOOP();

    _MOVE:
        ptr += IP->val;
        LOOP();
        
    _INCR:
        *ptr += IP->val;
        LOOP();
        
    _ZERO:
        ptr[0] = 0;
        LOOP();

    _PRINT:         
        std::cout << (*ptr);
        LOOP();

    _READ:
        std::cin.get(*ptr);
        LOOP();

    _TERMINATE:
        return;

    }

    static void verify_address_table_completeness(const std::map<Action,void*>& table)
    {
	for(auto a : ENUMERATED_ACTIONS){
            if(table.find(a) == table.end()){
		throw std::logic_error(to_string(a) + " not in address table");
            }
        }
    }
    
}


#include "bf_instruction.hpp"

namespace bf {

    void execute(std::vector<Instruction>&  _instructions)
    {
        std::vector<char> characters(30000);
        char* ptr = characters.data();
        const int sz = _instructions.size();
        const auto instructions = _instructions.data();

        for(int i=0; i<sz; i++){

            const auto& instr = instructions[i];

            switch(instr.action){

            case TRUEJUMP:
                if(*ptr){
                    i += instr.val;
                }
                break;

            case FALSEJUMP:
                if(!(*ptr)){
                    i += instr.val;
                }
                break;

            case MOVE:
                ptr += instr.val;
                break;

            case INCR:
                *ptr += instr.val;
                break;

            case ZERO:
                ptr[0] = 0;
                break;

            case PRINT:
                std::cout << (*ptr);
                break;

            case READ:
                std::cin.get(*ptr);
                break;

            case TERMINATE:
                break;
            }
        }

    }

}

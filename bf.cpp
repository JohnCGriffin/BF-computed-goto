
#include <fstream>

#include "bf_instruction.hpp"

namespace bf {

    using Instructions = std::vector<Instruction>;

    // Transform [-] triple into ZERO instruction
    static Instructions optimize(const Instructions instrs){
	Instructions result;
	for(auto& instr : instrs){
	    if(instr.action == TRUEJUMP){
		int sz = result.size();
		if(sz > 1 && result.at(sz-1).action == INCR && result.at(sz-2).action == FALSEJUMP){
		    result.pop_back();
		    result.pop_back();
		    result.push_back({ ZERO });
		    continue;
		}
	    }
	    result.push_back(instr);
	}
	return result;
    }

    static Instructions load_instructions(std::istream& is)
    {
        auto instructions = optimize(read_instructions(is));

        // WHILE LOOP PATCHING
	// The start of a loop is FALSEJUMP.
	// A loop terminates at TRUEJUMP.
    
        std::vector<int> while_stack;
        for(size_t i=0; i<instructions.size(); i++){
        
            if(instructions.at(i).action == FALSEJUMP){
                while_stack.push_back(i);
            }
        
            if(instructions.at(i).action == TRUEJUMP){
                int start = while_stack.back();
                instructions.at(start).val = (i - start);
                instructions.at(i).val = (start - i);
                while_stack.pop_back();
            }
        }

        instructions.push_back({ TERMINATE });

        return instructions;
    }

}


int main(int argc, char** argv)
{
    std::ifstream ifs;

    if(argc == 2){
        ifs.open(argv[1]);
        if(!ifs){
            std::cerr << "could not open " << argv[1] << std::endl;
            return 1;
        }
    }

    std::istream& is(argc == 2 ? ifs : std::cin);
    
    auto instrs = bf::load_instructions(is);

    bf::execute(instrs);

    return 0;
}

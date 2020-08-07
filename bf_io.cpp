

#include "bf_instruction.hpp"

#include <map>

namespace bf {
    
    std::vector<Instruction> read_instructions(std::istream& is)
    {
	static std::map<char,int> direction = {{'>', 1}, {'<', -1}, {'+', 1}, {'-', -1}};
	static std::map<char,Action>
	    charActions = {{ '>', MOVE },
			   { '<', MOVE },
			   { '+', INCR },
			   { '-', INCR },
			   { '[', FALSEJUMP },
			   { ']', TRUEJUMP },
			   { '.', PRINT },
			   { ',', READ }};

	std::vector<Instruction> instructions;
	char c;

	while(is >> c){
	    switch(c){
	    case '<':
	    case '>':
	    case '+':
	    case '-':
		{
		    int increment = direction.at(c);
		    Action action = charActions.at(c);
		    if(instructions.empty() || instructions.back().action != action){
			instructions.push_back({ action });
		    }
		    instructions.back().val += increment;
		}
		break;
	    case '.':
	    case ',':
	    case '[':
	    case ']':
		instructions.push_back({ charActions.at(c) });
		break;
	    }
	}
	
	return instructions;
    }

}

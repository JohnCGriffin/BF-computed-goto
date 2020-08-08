

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>


namespace bf {

#define ENUMERATED_ACTIONS { MOVE, INCR, TRUEJUMP, FALSEJUMP, ZERO, PRINT, READ, TERMINATE }
    
    enum Action ENUMERATED_ACTIONS;

    struct Instruction {
	Action action;
	short val;
	void* jump;
    };

    std::ostream& operator<<(std::ostream& os, const Action& action);
    std::string to_string(Action);


    std::vector<Instruction> read_instructions(std::istream& is);

    void execute(std::vector<Instruction>& instrs);

}

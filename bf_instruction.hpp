

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>


namespace bf {

    enum Action { MOVE, INCR, TRUEJUMP, FALSEJUMP, ZERO, PRINT, READ, TERMINATE };

    struct Instruction {
	Action action;
	short val;
	void* jump;
    };

    std::ostream& operator<<(std::ostream& os, const Action& action);


    std::vector<Instruction> read_instructions(std::istream& is);

    void execute(std::vector<Instruction>& instrs);

}

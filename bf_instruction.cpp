
#include "bf_instruction.hpp"

namespace bf {

    using namespace std;
    
    ostream& operator<<(ostream& os, const Action& action)
    {
#define ACTIONOUT(A) case A: return os << #A
	switch(action){
	    ACTIONOUT(MOVE);
	    ACTIONOUT(INCR);
	    ACTIONOUT(TRUEJUMP);
	    ACTIONOUT(FALSEJUMP);
	    ACTIONOUT(ZERO);
	    ACTIONOUT(PRINT);
	    ACTIONOUT(READ);
	    ACTIONOUT(TERMINATE);
	default:
	    throw logic_error(__FILE__ " unhandled Action case in operator<<");
	}
    }

}

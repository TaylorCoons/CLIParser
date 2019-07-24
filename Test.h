#include <iostream>
#include <cassert>

#include "CLIParser.h"

class Test {
/* Variables */

/* Functions */
public:
    Test();
    bool NoSubparser();
    bool RequiredArg();
    bool OptionalArg();
    bool NoArg();
    bool CompressedArg();
    bool RequiredOpt();
    bool OptionalOpt();
    bool InvalidOpt();
    bool InvalidUse();
    std::string optName;
    void TestAll();
    ~Test();  
};

#include "Test.h"

Test::Test() {

}

bool Test::NoSubparser() {
    CLIParser argParse;
    argParse.AddParser("", NULL);
    char** args = (char**)"argparse";
    std::string subParser = argParse.Parse(1, args);
    assert(subParser == "");
    assert(argParse.ParseError() == CLIParser::ERROR::OK); 
    return true;
}

bool Test::RequiredArg() {

    return true;
}

bool Test::OptionalArg() {

    return true;
}

bool Test::NoArg() {

    return true;
}

bool Test::CompressedArg() {

    return true;
}

bool Test::RequiredOpt() {

    return true;
}

bool Test::OptionalOpt() {

    return true;
}

bool Test::InvalidOpt() {

    return true;
}

bool Test::InvalidUse() {

    return true;
}

void Test::TestAll() {

}

Test::~Test() {

}

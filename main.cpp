#include <iostream>

#include "CLIParser.h"


int main(int argc, char** argv) {
    CLIParser argparse;
    CLIParser::OPTIONS options;
    options["username"] = { "--username", 
                        "-u", 
                        CLIParser::ARG_TYPE::REQUIRED_ARG, 
                        CLIParser::OPT_TYPE::OPTIONAL_OPT };
    options["email"] = { "--email", 
                        "-e", 
                        CLIParser::ARG_TYPE::OPTIONAL_ARG, 
                        CLIParser::OPT_TYPE::OPTIONAL_OPT };
    options["temp"] = { "--temp", 
                        "-t", 
                        CLIParser::ARG_TYPE::NO_ARG, 
                        CLIParser::OPT_TYPE::REQUIRED_OPT };
    argparse.AddParser("new", &options);
    argparse.AddParser("noop", NULL); 
    argparse.Parse(argc, argv);
    CLIParser::OPTIONS::iterator it;
    for (it = options.begin(); it != options.end(); it++) {
        std::cout << it->second.longOpt << " ";
        std::cout << "flag: " << (it->second.flag ? "true" : "false") << " ";
        std::cout << "result: " << it->second.result << " ";
        std::cout << std::endl;
    }
    return 0;
}

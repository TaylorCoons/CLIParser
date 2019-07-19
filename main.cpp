#include <iostream>

#include "CLIParser.h"


int main(int argc, char** argv) {
    CLIParser argparse;
    std::vector<CLIParser::OPTION> options;
    options.push_back({ "username", "u", CLIParser::ARG_TYPE::REQUIRED_ARGUMENT, "" });
    options.push_back({ "email", "e", CLIParser::ARG_TYPE::OPTIONAL_ARGUMENT, "" });
    options.push_back({ "temp", "t", CLIParser::ARG_TYPE::NO_ARGUMENT, "" });
    argparse.AddParser("new", &options); 
    argparse.Parse(argc, argv);
    for (int i = 0; i < options.size(); i++) {
        std::cout << options.at(i).longOpt << " ";
        std::cout << "flag: " << (options.at(i).flag ? "true" : "false") << " ";
        std::cout << "result: " << options.at(i).result << " ";
        std::cout << std::endl;
    }
    return 0;
}

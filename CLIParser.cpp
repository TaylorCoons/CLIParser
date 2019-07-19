#include "CLIParser.h"

CLIParser::CLIParser() {    
}

void CLIParser::AddParser(std::string subParser, std::vector<OPTION>* options) {
    ClearOutOptions(options);
    if (subParser == "") {
        parserOptions[""] = options; 
    } else {
        parserOptions[subParser] = options;
    }
}

void CLIParser::Tokenize(int argc, char** argv, std::vector<std::string>* args) {
    args->clear();
    for (unsigned int i = 1; i < argc; i++) {
        args->push_back(std::string(argv[i]));
    }
}

void CLIParser::SubParse(std::string subParser, std::vector<std::string>* args) {
    bool error = false;
    for (unsigned int i = 0; i < args->size(); i++) {
        int optionIndex = OptionIndex(subParser, args->at(i));
        if (optionIndex != -1) {
            switch (parserOptions[subParser]->at(optionIndex).argType) {
            case NO_ARG:
                if (i == args->size() - 1 
                    || (i != args->size() - 1 
                    && OptionIndex(subParser, args->at(i + 1)) != -1)) {
                    parserOptions[subParser]->at(optionIndex).flag = true;
                } else {
                    NoArgumentError(&parserOptions[subParser]->at(optionIndex));
                    error = true;
                }
            break;
            case OPTIONAL_ARG:
                if (i != args->size() - 1 
                    && OptionIndex(subParser, args->at(i + 1)) == -1) {
                    parserOptions[subParser]->at(optionIndex).result = args->at(i+1);
                    i++;
                }
                parserOptions[subParser]->at(optionIndex).flag = true;
            break;
            case REQUIRED_ARG:
                if (i != args->size() - 1 
                    && OptionIndex(subParser, args->at(i + 1)) == -1) {
                    parserOptions[subParser]->at(optionIndex).result = args->at(i+1);
                    i++;
                } else {
                    RequiredArgumentError(&parserOptions[subParser]->at(optionIndex));
                    error = true;
                }
                parserOptions[subParser]->at(optionIndex).flag = true;
            break;
            }
        } else {
            InvalidOptionError(&args->at(i));
            error = true;
        }
        if (error) {
            // Display usage
            return;
        }
    }
    for (unsigned int i = 0; i < parserOptions[subParser]->size(); i++) {
        OPTION option = parserOptions[subParser]->at(i);
        if (option.optType == REQUIRED_OPT && !option.flag) {
            RequiredOptionError(&option);
            return;
        }
    }
}

int CLIParser::OptionIndex(std::string subParser, std::string option) {
    for (unsigned int i = 0; i < parserOptions[subParser]->size(); i++) {
        if (parserOptions[subParser]->at(i).longOpt == option
            || parserOptions[subParser]->at(i).shortOpt == option) {
            return i;
        }
    }
    return -1;
}

void CLIParser::RequiredArgumentError(const OPTION* option) {
    std::cout << "Option " << option->longOpt << " (" << option->shortOpt << ")";
    std::cout << " requires argument";
    std::cout << std::endl;
    parseError = true;
}

void CLIParser::NoArgumentError(const OPTION* option) {
    std::cout << "Option " << option->longOpt << " (" << option->shortOpt << ")";
    std::cout << " does not take arguments";
    std::cout << std::endl;
    parseError = true;
}

void CLIParser::InvalidOptionError(const std::string* option) {
    std::cout << "Unexpected option: " << *option;
    std::cout << std::endl;
    parseError = true;
}

void CLIParser::InvalidUseError() {
    std::cout << "Invalid Use" << std::endl;
    parseError = true;
}

void CLIParser::RequiredOptionError(const OPTION* option) {
    std::cout << "Option: " << option->longOpt << " (" << option->shortOpt << ")";
    std::cout << " is required";
    std::cout << std::endl;
    parseError = true;
}

bool CLIParser::ParseError() {
    return parseError;
}

void CLIParser::ClearOutOptions(std::vector<OPTION>* parserOptions) {
    for (unsigned int i = 0; i < parserOptions->size(); i++) {
        parserOptions->at(i).flag = false;
        parserOptions->at(i).result = "";
    }
}

std::string CLIParser::Parse(int argc, char** argv) {
    parseError = false;
    std::vector<std::string> args;
    Tokenize(argc, argv, &args);
    std::string subParser = "";
    if (args.size() > 0 && parserOptions.count(args.at(0))) {
        subParser = args.at(0);
        args.erase(args.begin());
        SubParse(subParser, &args);
    } else if (parserOptions.count("")) {
        SubParse(subParser, &args);
    } else {
        InvalidUseError();
    }
    return subParser;
}

CLIParser::~CLIParser() {
}

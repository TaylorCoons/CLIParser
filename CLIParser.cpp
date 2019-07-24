#include "CLIParser.h"

CLIParser::CLIParser() {    
}

void CLIParser::AddParser(std::string subParser, OPTIONS* options) {
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
    OPTIONS* options = parserOptions[subParser];
    for (unsigned int i = 0; i < args->size(); i++) {
        std::string optionName = "";
        if (GetOptionFromTag(subParser, args->at(i), &optionName)) {
            switch (options->at(optionName).argType) {
            case NO_ARG:
                if (i == args->size() - 1 
                    || (i != args->size() - 1 
                    && GetOptionFromTag(subParser, args->at(i + 1)))) {
                    options->at(optionName).flag = true;
                } else {
                    NoArgumentError(&options->at(optionName));
                    error = true;
                }
            break;
            case OPTIONAL_ARG:
                if (i != args->size() - 1 
                    && !GetOptionFromTag(subParser, args->at(i + 1))) {
                    options->at(optionName).result = args->at(i + 1);
                    i++;
                }
                options->at(optionName).flag = true;
            break;
            case REQUIRED_ARG:
                if (i != args->size() - 1 
                    && !GetOptionFromTag(subParser, args->at(i + 1))) {
                    options->at(optionName).result = args->at(i + 1);
                    i++;
                } else {
                    RequiredArgumentError(&options->at(optionName));
                    error = true;
                }
                options->at(optionName).flag = true;
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
    if (options != NULL) {
        OPTIONS::iterator it;
        for (it = options->begin(); it != options->end(); it++) {
            OPTION option = it->second;
            if (option.optType == REQUIRED_OPT && !option.flag) {
                RequiredOptionError(&option);
                return;
            }
        }
    }
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

bool CLIParser::GetOptionFromTag(std::string subParser, 
                                 std::string tag,
                                 std::string* optionName) {
    OPTIONS* options = parserOptions.at(subParser);
    OPTIONS::iterator it;
    for (it = options->begin(); it != options->end(); it++) {
        if (it->second.longOpt == tag || it->second.shortOpt == tag) {
            if (optionName != NULL) {
                *optionName = it->first;
            }
            return true;
        }
    }
    return false;
}

bool CLIParser::ParseError() {
    return parseError;
}

void CLIParser::ClearOutOptions(OPTIONS* options) {
    if (options != NULL) {
        OPTIONS::iterator it;
        for (it = options->begin(); it != options->end(); it++) {
            it->second.flag = false;
            it->second.result = "";
        }
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

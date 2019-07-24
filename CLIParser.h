#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <string>


class CLIParser {
/* Variables */
public:
 
    enum ARG_TYPE {
        NO_ARG,
        REQUIRED_ARG,
        OPTIONAL_ARG
    };
    
    enum OPT_TYPE {
        REQUIRED_OPT,
        OPTIONAL_OPT
    };

    struct OPTION {
        std::string longOpt;
        std::string shortOpt;
        ARG_TYPE argType;
        OPT_TYPE optType;
        bool flag;
        std::string result;
    };
   
    enum ERROR {
        OK,
        ERROR_REQUIRED_ARG,
        ERROR_NO_ARG,
        ERROR_REQUIRED_OPT,
        ERROR_INVALID_OPT,
        ERROR_INVALID_USE
    };
    
    using OPTIONS = std::map<std::string, OPTION>;

private:
    std::map<std::string, OPTIONS*> parserOptions; 
    ERROR parseError;

/* Functions */
private:
    void Tokenize(int argc, char** argv, std::vector<std::string>* args);

    void SubParse(std::string subParser, std::vector<std::string>* args);

    void ClearOutOptions(OPTIONS* options);

    void RequiredArgumentError(const OPTION* option);

    void NoArgumentError(const OPTION* option);

    void RequiredOptionError(const OPTION* option);

    void InvalidOptionError(const std::string* option);

    void InvalidUseError();

    bool GetOptionFromTag(std::string subParser,
                          std::string tag, 
                          std::string* optionName = NULL);
    

public: 
   
    CLIParser();
    
    void AddParser(std::string subParser, OPTIONS* options);
    
    std::string Parse(int argc, char** argv);

    ERROR ParseError();

    ~CLIParser();

};

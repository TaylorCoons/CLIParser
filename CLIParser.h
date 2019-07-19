
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

private:
    std::map<std::string, std::vector<OPTION>*> parserOptions; 
    bool parseError;

/* Functions */
private:
    void Tokenize(int argc, char** argv, std::vector<std::string>* args);

    void SubParse(std::string subParser, std::vector<std::string>* args);

    int OptionIndex(std::string subParser, std::string option);

    void ClearOutOptions(std::vector<OPTION>* parserOptions);

    void RequiredArgumentError(const OPTION* option);

    void NoArgumentError(const OPTION* option);

    void RequiredOptionError(const OPTION* option);

    void InvalidOptionError(const std::string* option);

    void InvalidUseError();

public: 
   
    CLIParser();
    
    void AddParser(std::string subParser, std::vector<OPTION>* options);
    
    std::string Parse(int argc, char** argv);

    bool ParseError();

    ~CLIParser();

};

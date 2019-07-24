cliparser: main.cpp CLIParser.h CLIParser.cpp
	g++ -g -o argparse.exe CLIParser.h CLIParser.cpp main.cpp

test: blackboxtest.cpp Test.h Test.cpp CLIParser.h CLIParser.cpp
	g++ -g -o testparse.exe CLIParser.h CLIParser.cpp Test.h Test.cpp blackboxtest.cpp

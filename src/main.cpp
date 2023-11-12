#include "Lexer.hpp"
#include "LR1Parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cerr << "用法: " << argv[0] << " <输入文件> <文法文件>" << std::endl;
		return 1;
	}

	std::string inputFile = argv[1];
	std::string grammarFile = argv[2];

	std::ifstream file(inputFile);
	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << inputFile << std::endl;
		return 1;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string content = buffer.str();

	Lexer lexer(content);
	std::vector<Symbol> sentence;
	Token token;
	do {
		token = lexer.getNextToken();
		// std::cout << token.toString() << std::endl;
		sentence.push_back(Symbol(SymbolType::Terminal, token.toString()));
	} while (token.type != T_EOF);

	LR1Parser parser(grammarFile);
	parser.parse(sentence);

	return 0;
}

#include "Lexer.hpp"
#include "LR1Parser.hpp"
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) {
		std::cerr << "无法打开文件" << std::endl;
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
		std::cout << token.toString() << std::endl;
		sentence.push_back(Symbol(SymbolType::Terminal, token.toString()));
	} while (token.type != T_EOF);

	LR1Parser parser("grammer.txt");
	parser.parse(sentence);


	return 0;
}
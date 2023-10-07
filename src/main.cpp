#include "Lexer.hpp"
#include <iostream>

int main()
{
	Token token;
	std::string input;
	while (getline(std::cin, input)) {
		Lexer lexer(input);
		do {
			token = lexer.getNextToken();
			std::cout << token.toString() << std::endl;
		} while (token.type != T_EOF);
	}

	return 0;
}
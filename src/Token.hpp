#pragma once

#include <string>


enum TokenType {
	// 字面量 (Literals)
	T_IDENTIFIER,       // 例如: variableName, 任意其他变量名、函数名
	T_INTEGER_LITERAL,  // 例如: 42
	T_FLOAT_LITERAL,    // 例如: 3.14
	T_STRING_LITERAL,   // 例如: "hello"
	T_CHAR_LITERAL,     // 例如: 'a'

	// 关键字 (Keywords)
	T_IF,      // if
	T_ELSE,    // else
	T_WHILE,   // while
	T_FOR,     // for
	T_RETURN,  // return
	T_INT,     // int
	T_FLOAT,   // float
	T_CHAR,    // char
	T_VOID,    // void
	T_STRUCT,  // struct
	// ... 可以继续添加其他关键字，如: switch, case, etc.

	// 操作符 (Operators)
	T_PLUS,          // +
	T_MINUS,         // -
	T_MULTIPLY,      // *
	T_DIVIDE,        // /
	T_ASSIGN,        // =
	T_EQUAL,         // ==
	T_NOTEQUAL,      // !=
	T_LESS,          // <
	T_LESSEQUAL,     // <=
	T_GREATER,       // >
	T_GREATEREQUAL,  // >=
	T_AND,           // &&
	T_OR,            // ||
	T_NOT,           // !
	T_MOD,           // %
	T_INCREMENT,     // ++
	T_DECREMENT,     // --
	T_BITAND,        // &
	T_BITOR,         // |
	T_BITXOR,        // ^
	T_BITNOT,        // ~
	T_LEFTSHIFT,     // <<
	T_RIGHTSHIFT,    // >>
	// ... 其他操作符

	// 界符 (Delimiters/Punctuators)
	T_SEMICOLON,     // ;
	T_LEFT_BRACE,    // {
	T_RIGHT_BRACE,   // }
	T_LEFT_PAREN,    // (
	T_RIGHT_PAREN,   // )
	T_LEFT_SQUARE,   // [
	T_RIGHT_SQUARE,  // ]
	T_COMMA,         // ,
	T_DOT,           // .
	T_ARROW,         // ->
	T_COLON,         // :
	T_QUESTION,      // ?
	// ... 其他界符

	T_UNKNOWN,  // 未知Token
	T_EOF,      // 文件结束
};

struct Token
{
	Token(const TokenType& type, const std::string& value) : type(type), value(value) {}
	Token() {}

	TokenType type;
	std::string value;

	std::string toString()
	{
		return "Type: \t" + tokenTypeToString(type) + ", \tValue: \t" + value;
	};

private:
	std::string tokenTypeToString(TokenType type)
	{
		switch (type) {
			case T_IDENTIFIER:
				return "IDENTIFIER";
			case T_INTEGER_LITERAL:
				return "INTEGER_LITERAL";
			case T_FLOAT_LITERAL:
				return "FLOAT_LITERAL";
			case T_STRING_LITERAL:
				return "STRING_LITERAL";
			case T_CHAR_LITERAL:
				return "CHAR_LITERAL";
			case T_IF:
				return "IF";
			case T_ELSE:
				return "ELSE";
			case T_WHILE:
				return "WHILE";
			case T_FOR:
				return "FOR";
			case T_RETURN:
				return "RETURN";
			case T_INT:
				return "INT";
			case T_FLOAT:
				return "FLOAT";
			case T_CHAR:
				return "CHAR";
			case T_VOID:
				return "VOID";
			case T_STRUCT:
				return "STRUCT";
			case T_PLUS:
				return "PLUS";
			case T_MINUS:
				return "MINUS";
			case T_MULTIPLY:
				return "MULTIPLY";
			case T_DIVIDE:
				return "DIVIDE";
			case T_ASSIGN:
				return "ASSIGN";
			case T_EQUAL:
				return "EQUAL";
			case T_NOTEQUAL:
				return "NOTEQUAL";
			case T_LESS:
				return "LESS";
			case T_LESSEQUAL:
				return "LESSEQUAL";
			case T_GREATER:
				return "GREATER";
			case T_GREATEREQUAL:
				return "GREATEREQUAL";
			case T_AND:
				return "AND";
			case T_OR:
				return "OR";
			case T_NOT:
				return "NOT";
			case T_MOD:
				return "MOD";
			case T_INCREMENT:
				return "INCREMENT";
			case T_DECREMENT:
				return "DECREMENT";
			case T_BITAND:
				return "BITAND";
			case T_BITOR:
				return "BITOR";
			case T_BITXOR:
				return "BITXOR";
			case T_BITNOT:
				return "BITNOT";
			case T_LEFTSHIFT:
				return "LEFTSHIFT";
			case T_RIGHTSHIFT:
				return "RIGHTSHIFT";
			case T_SEMICOLON:
				return "SEMICOLON";
			case T_LEFT_BRACE:
				return "LEFT_BRACE";
			case T_RIGHT_BRACE:
				return "RIGHT_BRACE";
			case T_LEFT_PAREN:
				return "LEFT_PAREN";
			case T_RIGHT_PAREN:
				return "RIGHT_PAREN";
			case T_LEFT_SQUARE:
				return "LEFT_SQUARE";
			case T_RIGHT_SQUARE:
				return "RIGHT_SQUARE";
			case T_COMMA:
				return "COMMA";
			case T_DOT:
				return "DOT";
			case T_ARROW:
				return "ARROW";
			case T_COLON:
				return "COLON";
			case T_QUESTION:
				return "QUESTION";
			case T_UNKNOWN:
				return "UNKNOWN";
			case T_EOF:
				return "EOF";
			default:
				return "INVALID_TOKEN_TYPE";
		}
	}
};

#pragma once

#include <string>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <fstream>
#include <sstream>


enum class SymbolType {
	Terminal,     // 终结符
	NonTerminal,  // 非终结符
	Epsilon       // 空串
};

struct Symbol
{
	SymbolType type;
	std::string value;
	Symbol()
	{
		type = SymbolType::Epsilon;
		value = "";
	}
	Symbol(const SymbolType& type, const std::string& value) : type(type), value(value) {}

	std::string to_string() const
	{
		return value;  // 或者任何合适的表示方式
	}

	friend bool operator==(const Symbol& lhs, const Symbol& rhs)
	{
		return lhs.type == rhs.type && lhs.value == rhs.value;
	}

	friend bool operator<(const Symbol& lhs, const Symbol& rhs)
	{
		if (lhs.type < rhs.type) return true;
		if (rhs.type < lhs.type) return false;
		return lhs.value < rhs.value;
	}
};

struct Production
{
	Symbol lhs;               // 左手边，非终结符
	std::vector<Symbol> rhs;  // 右手边，非终结符和终结符的 组合

	Production() {}
	Production(Symbol lhs, std::vector<Symbol> rhs) : lhs(lhs), rhs(rhs) {}
	std::string to_string() const
	{
		std::string res;
		res += lhs.value + " -> ";
		for (auto& item : rhs) {
			res += item.value;
		}
		return "[" + res + "]";
	}

	friend bool operator==(const Production& lhs, const Production& rhs)
	{
		return lhs.lhs == rhs.lhs && lhs.rhs == rhs.rhs;
	}
	friend bool operator<(const Production& lhs, const Production& rhs)
	{
		if (lhs.lhs < rhs.lhs) return true;
		if (rhs.lhs < lhs.lhs) return false;
		return lhs.rhs < rhs.rhs;
	}
};

class LR1Item {
public:
	enum class State {
		SHIFT,   // 移进
		REDUCE,  // 归约
		GOTO,    // 待约
		ACCEPT   // 接受
	};

	LR1Item(Production production, size_t dot_position, Symbol lookahead)
	    : production(production), dot_position(dot_position), lookahead(lookahead) {}

	std::string to_string() const
	{
		std::string res;
		res += production.lhs.value + " -> ";
		size_t index = 0;
		for (auto& item : production.rhs) {
			if (index++ == dot_position) res += ".";
			res += item.value;
		}
		if (index++ == dot_position) res += ".";
		res += ", " + lookahead.value;
		return "[" + res + "]";
	}

	Symbol next_symbol() const
	{
		if (dot_position == production.rhs.size()) return Symbol(SymbolType::Epsilon, "");
		return production.rhs[dot_position];
	}

	Symbol nnext_symbol() const
	{
		if (dot_position == production.rhs.size()) return Symbol(SymbolType::Epsilon, "");

		LR1Item tmp = *this;
		tmp.dot_position++;
		return tmp.next_symbol();
	}

	Production production;
	size_t dot_position;
	Symbol lookahead;

	friend bool operator==(const LR1Item& lhs, const LR1Item& rhs)
	{
		return lhs.production == rhs.production &&
		       lhs.dot_position == rhs.dot_position &&
		       lhs.lookahead == rhs.lookahead;
	}

	friend bool operator<(const LR1Item& lhs, const LR1Item& rhs)
	{
		if (lhs.production < rhs.production) return true;
		if (rhs.production < lhs.production) return false;
		if (lhs.dot_position < rhs.dot_position) return true;
		if (rhs.dot_position < lhs.dot_position) return false;
		return lhs.lookahead < rhs.lookahead;
	}
};

struct Action
{
	enum class Type {
		SHIFT,
		REDUCE,
		ACCEPT,
		ERROR
	};
	Type type;
	size_t number;          // shift的新状态编号
	Production production;  // reduce使用的产生式

	Action() {}
	Action(const Type& type, const size_t& number, const Production& production) : type(type), number(number), production(production) {}

	std::string to_string() const
	{
		switch (type) {
			case Type::SHIFT:
				return "S " + std::to_string(number);
			case Type::REDUCE:
				return "R " + production.to_string();
			case Type::ACCEPT:
				return "Accept";
			case Type::ERROR:
				return "x";
		}
		return "";
	}
};


class LR1Parser {
public:
	LR1Parser(const std::vector<Production>& productions, Symbol start, Symbol end);
	LR1Parser(const std::string file_path);

	void print_firstSet() const;
	void print_tables() const;
	bool parse(const std::vector<Symbol>& sentence) const;

private:
	void parseEBNFLine(const std::string& line);
	void print_stacks(const std::stack<int>& stateStack,
	                  const std::stack<Symbol>& symbolStack,
	                  const std::vector<Symbol>& inputStack) const;

	void construct_tables();
	/**
	 * @brief 求项目集族的闭包
	 *
	 * @param lr1ItemSet 待求闭包的项目集族
	 * @return std::set<LR1Item> 该项目集族的闭包
	 */
	std::set<LR1Item> closure(std::set<LR1Item> lr1ItemSet) const;

private:
	/**
	 * @brief 获取一个LR1项目当前的状态(移进、归约、接受、待约)
	 *
	 * @param item LR1项目
	 * @return LR1Item::State 状态
	 */
	LR1Item::State get_lr1item_state(const LR1Item& item) const;

	/**
	 * @brief 获取由某非终结符为产生式左边的所有产生式
	 *
	 * @param symbol 非终结符
	 * @return std::vector<Production> 所有产生式
	 */
	std::vector<Production> get_productions_start_by_symbol(const Symbol& symbol) const;

private:  // 求FIRST集
	void calculateFirstSets();
	std::set<Symbol> firstString(std::vector<Symbol> content) const;

private:
	std::vector<Production> productions;
	std::map<Symbol, std::vector<Production>> productionMap;
	std::map<Symbol, std::set<Symbol>> firstSet, followSet;

	Symbol start_symbol;  // 起始符
	Symbol end_symbol;    // 终止符


	std::map<std::pair<int, Symbol>, Action> actionTable;  // ACTION表
	std::map<std::pair<int, Symbol>, int> gotoTable;       // GOTO表
	std::vector<std::set<LR1Item>> lr1ItemSets;            // 项目集族

	std::set<std::string> terminals;  // 终结符集
};

#pragma once
#include <string>

#include "Token.h"

struct Node
{
	virtual ~Node() = default;
};

struct NumNode : Node
{
	int value;
	NumNode(int value) : value(value) {}
};

struct IdNode : Node
{
	std::string name;
	IdNode(std::string name) : name(std::move(name)) {}
};

struct IfNode : Node
{
	Node* condition;
	Node* then_branch;
	Node* else_branch;
	IfNode(Node* condition, Node* then, Node* else_) : condition(condition), then_branch(then), else_branch(else_) {}
};

struct AssignNode : Node
{
	std::string name;
	Node* identifier;
	Node* value;
	TokenType assign_type;
	AssignNode(std::string name, Node* identifier, Node* value, TokenType assign_type) : name(std::move(name)), identifier(identifier), value(value), assign_type(assign_type) {}
};

struct BinOpNode : Node
{
	std::string op;
	Node* left;
	Node* right;
	BinOpNode(std::string op, Node* left, Node* right) : op(std::move(op)), left(left), right(right) {}
};
#include "AbstractSyntaxTreeHelper.h"

#include <iostream>
#include <ostream>

void AbstractSyntaxTreeHelper::printAST(Node* node, SymbolTable variables)
{
	if (node == nullptr)
		return;
	if (dynamic_cast<NumNode*>(node) != nullptr)
	{
		std::cout << dynamic_cast<NumNode*>(node)->value << std::endl;
	}
	else if (dynamic_cast<IdNode*>(node) != nullptr)
	{
		std::cout << variables.getVariable(dynamic_cast<IdNode*>(node)->name) << std::endl;
	}
	else if (dynamic_cast<BinOpNode*>(node) != nullptr)
	{
		std::cout << dynamic_cast<BinOpNode*>(node)->op << std::endl;
		printAST(dynamic_cast<BinOpNode*>(node)->left, variables);
		printAST(dynamic_cast<BinOpNode*>(node)->right, variables);
	}
	else if (dynamic_cast<IfNode*>(node) != nullptr)
	{
		const IfNode* if_node = dynamic_cast<IfNode*>(node);
		std::cout << "if" << std::endl;
		printAST(if_node->condition, variables);
		std::cout << "then" << std::endl;
		printAST(if_node->then_branch, variables);
		std::cout << "else" << std::endl;
		printAST(if_node->else_branch, variables);
	}
	else if (dynamic_cast<AssignNode*>(node) != nullptr)
	{
		const AssignNode* assign_node = dynamic_cast<AssignNode*>(node);
		std::cout << "assign" << std::endl;
		std::cout << assign_node->name << std::endl;
		printAST(assign_node->value, variables);
	}
}

void AbstractSyntaxTreeHelper::deallocateAST(Node* node)
{
	if (node == nullptr)
		return;
	if (dynamic_cast<NumNode*>(node) != nullptr)
	{
		delete dynamic_cast<NumNode*>(node);
		node = nullptr;
	}
	else if (dynamic_cast<IdNode*>(node) != nullptr)
	{
		delete dynamic_cast<IdNode*>(node);
		node = nullptr;
	}
	else if (dynamic_cast<BinOpNode*>(node) != nullptr)
	{
		deallocateAST(dynamic_cast<BinOpNode*>(node)->left);
		deallocateAST(dynamic_cast<BinOpNode*>(node)->right);
		delete dynamic_cast<BinOpNode*>(node);
		node = nullptr;
	}
	else if (dynamic_cast<IfNode*>(node) != nullptr)
	{
		const IfNode* if_node = dynamic_cast<IfNode*>(node);
		deallocateAST(if_node->condition);
		deallocateAST(if_node->then_branch);
		deallocateAST(if_node->else_branch);
		delete if_node;
		node = nullptr;
	}
	else if (dynamic_cast<AssignNode*>(node) != nullptr)
	{
		const AssignNode* assign_node = dynamic_cast<AssignNode*>(node);
		deallocateAST(assign_node->identifier);
		deallocateAST(assign_node->value);
		delete assign_node;
		node = nullptr;
	}
	else
	{
		throw std::runtime_error("Unknown node type");
	}
}

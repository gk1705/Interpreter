#include "Interpreter.h"

int Interpreter::interpret(Node* node)
{
	if (node == nullptr)
	{
		throw std::runtime_error("Root is null");
	}

	if (dynamic_cast<NumNode*>(node) != nullptr)
	{
		return interpretNumNode(dynamic_cast<NumNode*>(node));
	}
	if (dynamic_cast<IdNode*>(node) != nullptr)
	{
		return interpretIdNode(dynamic_cast<IdNode*>(node));
	}
	if (dynamic_cast<BinOpNode*>(node) != nullptr)
	{
		return interpretBinOpNode(dynamic_cast<BinOpNode*>(node));
	}
	if (dynamic_cast<AssignNode*>(node) != nullptr)
	{
		return interpretAssignNode(dynamic_cast<AssignNode*>(node));
	}
	if (dynamic_cast<IfNode*>(node) != nullptr)
	{
		interpretIfNode(dynamic_cast<IfNode*>(node));
		return 0;
	}
	throw std::runtime_error("Unknown node type");
}

int Interpreter::interpretNumNode(const NumNode* node)
{
	return node->value;
}

int Interpreter::interpretIdNode(const IdNode* node) const
{
	return variables.getVariable(node->name);
}

int Interpreter::interpretBinOpNode(const BinOpNode* node)
{
	const int left = interpret(node->left);
	const int right = interpret(node->right);

	if (node->op == "+") return left + right;
	else if (node->op == "-") return left - right;
	else if (node->op == "*") return left * right;
	else if (node->op == "/") return left / right;
	else if (node->op == ">") return left > right;
	else if (node->op == "<") return left < right;
	else if (node->op == ">=") return left >= right;
	else if (node->op == "<=") return left <= right;
	else if (node->op == "==") return left == right;
	else if (node->op == "!=") return left != right;
	else
		throw std::runtime_error("Unknown operator");
}

int Interpreter::interpretAssignNode(const AssignNode* node)
{
	const int value = interpret(node->value);
	int variable = variables.getVariable(node->name);

	if (node->assign_type == TokenType::ASSIGN) variable = value;
	else if (node->assign_type == TokenType::PLUSASSIGN) variable += value;
	else if (node->assign_type == TokenType::MINUSASSIGN) variable -= value;
	else if (node->assign_type == TokenType::MULASSIGN) variable *= value;
	else if (node->assign_type == TokenType::DIVASSIGN) variable /= value;
	else
		throw std::runtime_error("Unknown assignment type");

	variables.setVariable(node->name, variable);
	return variable;
}

void Interpreter::interpretIfNode(const IfNode* node)
{
	const int conditionValue = interpret(node->condition);
	if (conditionValue != 0)
	{
		interpret(node->then_branch);
	}
	else
	{
		interpret(node->else_branch);
	}
}


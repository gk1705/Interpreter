#include "Parser.h"

#include <stdexcept>

Node* Parser::parse()
{
	if (tokens[position].type == TokenType::IF)
	{
		return if_expr();
	}
	else
	{
		return assignment();
	}
}

Token& Parser::current_token()
{
	return tokens[position];
}

void Parser::eat(TokenType type)
{
	if (current_token().type == type)
	{
		position++;
	}
	else
	{
		throw std::runtime_error("Unexpected token");
	}
}

Node* Parser::factor()
{
	const Token& token = current_token();
	if (token.type == TokenType::INTEGER)
	{
		eat(TokenType::INTEGER);
		return new NumNode(std::stoi(token.value));
	}
	else if (token.type == TokenType::LPAREN)
	{
		eat(TokenType::LPAREN);
		Node* node = assignment();
		eat(TokenType::RPAREN);
		return node;
	}
	else if (token.type == TokenType::IDENTIFIER)
	{
		eat(TokenType::IDENTIFIER);
		return new IdNode(token.value);
	}
	else
	{
		throw std::runtime_error("Unexpected token");
	}
}

Node* Parser::term()
{
	Node* node = factor();
	while (position < tokens.size() && (current_token().type == TokenType::MUL || current_token().type == TokenType::DIV))
	{
		const Token& token = current_token();
		if (token.type == TokenType::MUL)
		{
			eat(TokenType::MUL);
		}
		else if (token.type == TokenType::DIV)
		{
			eat(TokenType::DIV);
		}
		node = new BinOpNode(token.value, node, factor());
	}
	return node;
}

Node* Parser::expr()
{
	Node* node = term();
	while (position < tokens.size() && (current_token().type == TokenType::PLUS || current_token().type == TokenType::MINUS))
	{
		const Token& token = current_token();
		if (token.type == TokenType::PLUS)
		{
			eat(TokenType::PLUS);
		}
		else if (token.type == TokenType::MINUS)
		{
			eat(TokenType::MINUS);
		}
		node = new BinOpNode(token.value, node, term());
	}
	return node;
}

Node* Parser::comp_expr()
{
	Node* node = expr();
	while (position < tokens.size() && (current_token().type == TokenType::GT || current_token().type == TokenType::LT || current_token().type == TokenType::GTE || current_token().type == TokenType::LTE || current_token().type == TokenType::EQ || current_token().type == TokenType::NEQ))
	{
		const Token& token = current_token();
		if (token.type == TokenType::GT)
		{
			eat(TokenType::GT);
		}
		else if (token.type == TokenType::LT)
		{
			eat(TokenType::LT);
		}
		else if (token.type == TokenType::GTE)
		{
			eat(TokenType::GTE);
		}
		else if (token.type == TokenType::LTE)
		{
			eat(TokenType::LTE);
		}
		else if (token.type == TokenType::EQ)
		{
			eat(TokenType::EQ);
		}
		else if (token.type == TokenType::NEQ)
		{
			eat(TokenType::NEQ);
		}
		node = new BinOpNode(token.value, node, expr());
	}
	return node;
}

Node* Parser::if_expr()
{
	eat(TokenType::IF);
	Node* condition = assignment();
	eat(TokenType::THEN);
	Node* then_branch = assignment();
	eat(TokenType::ELSE);
	Node* else_branch = assignment();
	return new IfNode(condition, then_branch, else_branch);
}

Node* Parser::assignment()
{
	Node* node = comp_expr();
	while (position < tokens.size() && (current_token().type == TokenType::ASSIGN || current_token().type == TokenType::PLUSASSIGN || current_token().type == TokenType::MINUSASSIGN || current_token().type == TokenType::MULASSIGN || current_token().type == TokenType::DIVASSIGN))
	{
		const Token& token = current_token();
		if (token.type == TokenType::ASSIGN)
		{
			eat(TokenType::ASSIGN);
		}
		else if (token.type == TokenType::PLUSASSIGN)
		{
			eat(TokenType::PLUSASSIGN);
		}
		else if (token.type == TokenType::MINUSASSIGN)
		{
			eat(TokenType::MINUSASSIGN);
		}
		else if (token.type == TokenType::MULASSIGN)
		{
			eat(TokenType::MULASSIGN);
		}
		else if (token.type == TokenType::DIVASSIGN)
		{
			eat(TokenType::DIVASSIGN);
		}

		Node* right = comp_expr();
		if (dynamic_cast<IdNode*>(node) != nullptr)
		{
			const std::string name = dynamic_cast<IdNode*>(node)->name;
			node = new AssignNode(name, node, right, token.type);
		}
		else
			throw std::runtime_error("Left side of assignment must be an identifier");
	}
	return node;
}

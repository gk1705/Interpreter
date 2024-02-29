#include "Lexer.h"

std::vector<Token> Lexer::tokenize()
{
	std::vector<Token> tokens;
	while (current_char != '\0')
	{
		if (std::isspace(current_char))
		{
			skip_whitespace();
			continue;
		}
		if (std::isdigit(current_char))
		{
			tokens.push_back(number());
			continue;
		}

		switch (current_char)
		{
		case '+': handle_operator_length(tokens, TokenType::PLUS, TokenType::PLUSASSIGN, '+'); break;
		case '-': handle_operator_length(tokens, TokenType::MINUS, TokenType::MINUSASSIGN, '-'); break;
		case '*': handle_operator_length(tokens, TokenType::MUL, TokenType::MULASSIGN, '*'); break;
		case '/': handle_operator_length(tokens, TokenType::DIV, TokenType::DIVASSIGN, '/'); break;
		case '(': tokens.emplace_back(TokenType::LPAREN, "("); break;
		case ')': tokens.emplace_back(TokenType::RPAREN, ")"); break;
		case '>': handle_operator_length(tokens, TokenType::GT, TokenType::GTE, '>'); break;
		case '<': handle_operator_length(tokens, TokenType::LT, TokenType::LTE, '<'); break;
		case '=': handle_operator_length(tokens, TokenType::ASSIGN, TokenType::EQ, '='); break;
		case '!': handle_operator_length(tokens, TokenType::NEGATION, TokenType::NEQ, '!'); break;
		default:
			{
				if (std::isalpha(current_char) || current_char == '_')
				{
					tokens.push_back(identifier());
					continue;
				}
				else
				{
					tokens.emplace_back(TokenType::UNKNOWN, std::string(1, current_char));
				}
				break;
			}
		}
		advance();
	}
	tokens.emplace_back(TokenType::EOS, "");
	return tokens;
}

char Lexer::peek() const
{
	if (position + 1 >= input.length())
		return '\0';
	return input[position + 1];
}

void Lexer::advance()
{
	position++;
	if (position > input.length() - 1)
		current_char = '\0';
	else
		current_char = input[position];
}

void Lexer::skip_whitespace()
{
	while (current_char != '\0' && std::isspace(current_char))
		advance();
}

Token Lexer::number()
{
	std::string result;
	while (current_char != '\0' && std::isdigit(current_char))
	{
		result += current_char;
		advance();
	}
	return {TokenType::INTEGER, result};
}

Token Lexer::identifier()
{
	std::string result;
	while (current_char != '\0' && (std::isalnum(current_char) || current_char == '_'))
	{
		result += current_char;
		advance();
	}

	if (result == "if")
		return {TokenType::IF, result};
	else if (result == "then")
		return {TokenType::THEN, result};
	else if (result == "else")
		return {TokenType::ELSE, result};
	// code to recognize further keywords would go here
	return {TokenType::IDENTIFIER, result};
}

void Lexer::handle_operator_length(std::vector<Token>& tokens, TokenType singleop, TokenType dualop, char op)
{
	if (peek() == '=')
	{
		advance();
		tokens.emplace_back(dualop, std::string(1, op) + "=");
	}
	else
	{
		tokens.emplace_back(singleop, std::string(1, op));
	}
}

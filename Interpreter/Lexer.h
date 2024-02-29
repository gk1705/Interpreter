#pragma once
#include <string>
#include <vector>

#include "Token.h"

class Lexer
{
public:
    Lexer(const std::string& input) : input(input), position(0), current_char(input[0]) {}

    std::vector<Token> tokenize();

private:
    std::string input;
    size_t position;
    char current_char;

    char peek() const;
    void advance();
    void skip_whitespace();
    Token number();
    Token identifier();
    void handle_operator_length(std::vector<Token>& tokens, TokenType singleop, TokenType dualop, char op);
};

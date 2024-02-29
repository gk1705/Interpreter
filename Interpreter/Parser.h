#pragma once
#include <vector>

#include "Node.h"

class Parser
{
public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), position(0) {}

    Node* parse();

private:
    std::vector<Token> tokens;
    size_t position;

    Token& current_token();
    void eat(TokenType type);
    Node* factor();
    Node* term();
    Node* expr();
    Node* comp_expr();
    Node* if_expr();
    Node* assignment();
};

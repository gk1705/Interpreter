#pragma once
#include <string>

enum class TokenType
{
    INTEGER, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN,
    GT, LT, GTE, LTE, EQ, NEQ,
    IF, ELSE, THEN,
    IDENTIFIER, ASSIGN, NEGATION, PLUSASSIGN, MINUSASSIGN, MULASSIGN, DIVASSIGN,
    EOS,
    UNKNOWN
};

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(std::move(value)) {}
};
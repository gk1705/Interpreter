#pragma once

#include "Node.h"
#include "SymbolTable.h"

class AbstractSyntaxTreeHelper
{
public:
    AbstractSyntaxTreeHelper() = delete;

    static void printAST(Node* node, SymbolTable variables);
    static void deallocateAST(Node* node);
};

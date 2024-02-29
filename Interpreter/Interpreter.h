#pragma once

#include "Node.h"
#include "SymbolTable.h"

class Interpreter
{
public:
    Interpreter(SymbolTable& variables) : variables(variables) {}
    int interpret(Node* node);

private:
    SymbolTable& variables;

    int interpretNumNode(const NumNode* node);
    int interpretIdNode(const IdNode* node) const;
    int interpretBinOpNode(const BinOpNode* node);
    int interpretAssignNode(const AssignNode* node);
    void interpretIfNode(const IfNode* node);
};

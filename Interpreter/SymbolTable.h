#pragma once
#include <stdexcept>
#include <unordered_map>

class SymbolTable
{
public:
    std::unordered_map<std::string, int> variables;

    void setVariable(const std::string& name, int value);

    int getVariable(const std::string& name);
};

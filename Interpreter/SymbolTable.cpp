#include "SymbolTable.h"

void SymbolTable::setVariable(const std::string& name, int value)
{
	variables[name] = value;
}

int SymbolTable::getVariable(const std::string& name)
{
	if (variables.find(name) == variables.end())
		throw std::runtime_error("Variable not found");
	return variables[name];
}
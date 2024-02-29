#include "Parser.h"

#include <iostream>

#include "AbstractSyntaxTreeHelper.h"
#include "Interpreter.h"
#include "Lexer.h"
#include "SymbolTable.h"

void Test()
{
    SymbolTable variables;
    variables.setVariable("player_attack", 5);
    variables.setVariable("enemy_health", 20);

    Lexer lexer("if player_attack + 2 == (player_attack += 2) then enemy_health -= (player_attack *= 2) else enemy_health += 10");
    const std::vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    Node* tree = parser.parse();

    Interpreter interpreter(variables);
    interpreter.interpret(tree);

    std::cout << "player_attack: " << variables.getVariable("player_attack") << std::endl;
    std::cout << "enemy_health: " << variables.getVariable("enemy_health") << std::endl;

    AbstractSyntaxTreeHelper::printAST(tree, variables);
    AbstractSyntaxTreeHelper::deallocateAST(tree);
}

int main()
{
    Test();
    std::cout << "Program finished executing" << std::endl;
    return 0;
}

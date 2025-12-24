#ifndef PARSING_HPP
# define PARSING_HPP

# include <iostream>
# include <algorithm>
# include <string>
# include <vector>
# include "Rule.hpp"
# include "FactNode.hpp"
# include <map>

enum EqualityType {
    EMPTY,
    IMPLICATION,
    BICONDITIONAL
};

struct RuleString {
    std::string condition;
    std::string conclusion;
    EqualityType equalityType;
};

struct RuleSet {

    std::string facts;
    std::string querry;
    std::vector<RuleString> rules;
};

struct SimulationState {
    std::unordered_map<char, FactNode*> facts;
    std::vector<Rule> rules;
};

struct Token {
    enum Type { FACT, OPERATOR, LPAREN, RPAREN };
    Type type;
    char value;
};

bool isOperator(char c);

RuleSet parse(std::vector<std::string> &lines, int ac, char **av);
void preprocessLine(std::string &line);

SimulationState buildASTNodes(const RuleSet &ruleSet);
std::map<char, FactState> getAllLetters(const RuleSet &ruleSet);
void cleanupCreatedNodes();

#endif
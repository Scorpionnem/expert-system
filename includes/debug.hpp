#ifndef DEBUG_HPP
# define DEBUG_HPP

#include "Rule.hpp"
#include <vector>
#include "parsing.hpp"

void printToken(const Token &token);
void printAllFacts(const std::unordered_map<char, FactNode*> &facts);
void printAllRules(const std::vector<Rule> &rules);

#endif
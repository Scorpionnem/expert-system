#include "parsing.hpp"

bool isOperator(char c) {
    return (
        c == '+' || c == '|'
        || c == '^' || c == '!'
    );
}

bool isParenthesis(char c) {
    return (c == '(' || c == ')');
}

bool isSymbol(char c) {
    return (
        isOperator(c) || isParenthesis(c)
        || c == '=' || c == '>'
        || c == '<' || c == '?'
    );
}

void	preprocessLine(std::string &line)
{
	line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
	line = line.substr(0, line.find('#'));
}

bool checkParentheses(const std::string &line) {
    int parentheses = 0;
    for (char c : line) {
        if (c == '(') parentheses++;
        else if (c == ')') {
            parentheses--;
            if (parentheses < 0) return false;
        }
    }
    return parentheses == 0;
}

bool checkFactsLine(const std::string &facts, std::map<char, FactState> letters) {

    std::string uniqueFacts;
    for (char c : facts) {
        if (!std::isupper(c)) return false;
        if (letters.find(c) == letters.end()) return false;
        if (uniqueFacts.find(c) == std::string::npos) uniqueFacts.push_back(c);
        else return false;
    }
    return true;
}

bool checkRulesLine(const std::string &line) {
    int parentheses = 0;
    if (line.empty()) return false;
    for (char c : line) {
        if (!isOperator(c) && !std::isupper(c) && !isParenthesis(c)) return false;
        if (c == '(') parentheses++;
        else if (c == ')') {
            parentheses--;
            if (parentheses < 0) return false;
        }
    }
    return !parentheses;
}

RuleSet parse(std::vector<std::string> &lines, int ac, char **av) {

    RuleSet ruleSet;

    if (ac >= 3) ruleSet.facts = std::string(av[2]);
    if (ac == 4) ruleSet.querry = std::string(av[3]);
    for (const std::string &line : lines) {
        for (char c : line)
            if (!isSymbol(c) && !std::isupper(c)) throw std::runtime_error("[ERROR] Invalid character found. : " + c);

        if (line[0] == '=') {
            if (ac >= 3) continue;
            if (!ruleSet.facts.empty()) throw std::runtime_error("[ERROR] Multiple facts lines found.");
            ruleSet.facts = line.substr(1);
        } else if (line[0] == '?') {
            if (ac == 4) continue;
            if (!ruleSet.querry.empty()) throw std::runtime_error("[ERROR] Multiple querry lines found.");
            ruleSet.querry = line.substr(1);
        } else {
            size_t pos;
            EqualityType type = EMPTY;
            if ((pos = line.find("<=>")) != std::string::npos) type = BICONDITIONAL;
            else if ((pos = line.find("=>")) != std::string::npos) type = IMPLICATION;
            else if (type == EqualityType::EMPTY) throw std::runtime_error("[ERROR] Invalid rule format: " + line);

            RuleString rule;
            rule.condition = line.substr(0, pos);
            rule.conclusion = line.substr(pos + (type == IMPLICATION ? 2 : 3));
            rule.equalityType = type;
            if (!checkRulesLine(rule.condition) || !checkRulesLine(rule.conclusion))
                throw std::runtime_error("[ERROR] Invalid characters in rule: " + line);
            ruleSet.rules.push_back(rule);
        }
    }
    if (ruleSet.facts.empty() || ruleSet.querry.empty())
        throw std::runtime_error("[ERROR] Missing facts or querry line.");

    std::map<char, FactState> letters = getAllLetters(ruleSet);
    if (!checkFactsLine(ruleSet.facts, letters) || !checkFactsLine(ruleSet.querry, letters))
        throw std::runtime_error("[ERROR] Invalid facts or querry line.");

    return ruleSet;
}

#include "parsing.hpp"
#include "ConditionNode.hpp"
#include "Rule.hpp"
#include <algorithm>


void printToken(const Token &token) {
    switch (token.type) {
        case Token::FACT:
            std::cout << "FACT('" << token.value << "')";
            break;
        case Token::OPERATOR:
            std::cout << "OP('" << token.value << "')";
            break;
        case Token::LPAREN:
            std::cout << "LPAREN";
            break;
        case Token::RPAREN:
            std::cout << "RPAREN";
            break;
    }
}

void printTokens(const std::vector<Token> &tokens) {
    std::cout << "Tokens: [";
    for (size_t i = 0; i < tokens.size(); i++) {
        printToken(tokens[i]);
        if (i < tokens.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void printAST(ASTNode* node, const std::string &prefix = "", bool isLeft = true) {
    if (node == nullptr) return;
    std::cout << prefix;
    std::cout << (isLeft ? "├── " : "└── ");
    FactNode* fact = dynamic_cast<FactNode*>(node);
    if (fact) {
        std::cout << "FACT: " << fact->c << " [" << fact->state << "]" << std::endl;
        return;
    }
    ConditionNode* cond = dynamic_cast<ConditionNode*>(node);
    if (cond) {
        std::cout << cond->type << std::endl;
        std::string newPrefix = prefix + (isLeft ? "│   " : "    ");
        if (cond->type == ConditionType::NOT) printAST(cond->left, newPrefix, false);
        else {
            if (cond->right != nullptr) {
                printAST(cond->left, newPrefix, true);
                printAST(cond->right, newPrefix, false);
            } else printAST(cond->left, newPrefix, false);
        }
    }
}

void printAllRules(const std::vector<Rule> &rules) {
    for (size_t i = 0; i < rules.size(); i++) {
        std::cout << "\n[Règle " << i + 1 << "] " << rules[i]._conditionString << " => " << rules[i]._conclusionString << std::endl;
        std::cout << "  Condition:" << std::endl;
        printAST(rules[i]._condition, "    ");
        std::cout << "  Conclusion:" << std::endl;
        printAST(rules[i]._conclusion, "    ");
    }
}

void printAllFacts(const std::unordered_map<char, FactNode*> &facts) {
    std::vector<char> keys;
    for (const auto &pair : facts) keys.push_back(pair.first);
    std::sort(keys.begin(), keys.end());
    for (char key : keys)
        std::cout << "  " << key << " : " << facts.at(key)->state << std::endl;
}

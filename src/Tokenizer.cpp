#include "parsing.hpp"
#include "Rule.hpp"
#include "map"

#include <string>
#include <vector>
#include <stack>
#include <cctype>

std::vector<ASTNode*> allCreatedNodes;

int getPrecedence(char op) {
    switch (op) {
        case '!': return 4;
        case '+': return 3;
        case '^': return 2;
        case '|': return 1;
        default: return 0;
    }
}

void cleanupCreatedNodes() {
    for (ASTNode* node : allCreatedNodes) delete node;
    allCreatedNodes.clear();
}

std::vector<Token> tokenize(const std::string &expr) {
    std::vector<Token> tokens;

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if (std::isspace(c)) continue;
        if (std::isupper(c)) tokens.push_back({Token::FACT, c});
        else if (isOperator(c)) tokens.push_back({Token::OPERATOR, c});
        else if (c == '(') tokens.push_back({Token::LPAREN, c});
        else if (c == ')') tokens.push_back({Token::RPAREN, c});
        else throw std::runtime_error(std::string("Invalid character: ") + c);
    }

    return tokens;
}

std::vector<Token> toPostfix(const std::vector<Token> &tokens) {
    std::vector<Token> output;
    std::stack<Token> operators;

    for (const Token &token : tokens) {
        switch (token.type) {
            case Token::FACT:
                output.push_back(token);
                break;
            case Token::OPERATOR: {
                while (!operators.empty() && operators.top().type == Token::OPERATOR &&
                       getPrecedence(operators.top().value) >= getPrecedence(token.value)) {
                    output.push_back(operators.top());
                    operators.pop();
                }
                operators.push(token);
                break;
            }
            case Token::LPAREN:
                operators.push(token);
                break;
            case Token::RPAREN:
                while (!operators.empty() && operators.top().type != Token::LPAREN) {
                    output.push_back(operators.top());
                    operators.pop();
                }
                if (operators.empty()) throw std::runtime_error("Mismatched parentheses");
                operators.pop();
                break;
        }
    }

    while (!operators.empty()) {
        if (operators.top().type == Token::LPAREN) throw std::runtime_error("Mismatched parentheses");
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

ASTNode* buildASTFromPostfix(const std::vector<Token> &postfix, std::unordered_map<char, FactNode*> &facts) {
    std::stack<ASTNode*> stack;

    for (const Token &token : postfix) {
        if (token.type == Token::FACT) stack.push(facts[token.value]);
        else if (token.type == Token::OPERATOR) {
            if (token.value == '!') {
                if (stack.empty()) throw std::runtime_error("Invalid expression: not enough operands");
                ASTNode* operand = stack.top();
                stack.pop();

                ConditionNode *node = new ConditionNode(ConditionType::NOT, operand);
                stack.push(node);
                allCreatedNodes.push_back(node);
            }
            else {
                if (stack.size() < 2) throw std::runtime_error("Invalid expression: not enough operands");

                ASTNode* right = stack.top();
                stack.pop();
                ASTNode* left = stack.top();
                stack.pop();

                ConditionType type;
                switch (token.value) {
                    case '+': type = ConditionType::AND; break;
                    case '|': type = ConditionType::OR; break;
                    case '^': type = ConditionType::XOR; break;
                    default: throw std::runtime_error("Unknown operator");
                }
                ConditionNode *node = new ConditionNode(type, left, right);
                stack.push(node);
                allCreatedNodes.push_back(node);
            }
        }
    }

    if (stack.size() != 1) throw std::runtime_error("Invalid expression: too many operands");

    return stack.top();
}

ASTNode* parseExpression(const std::string &expr, std::unordered_map<char, FactNode*> &facts) {
    if (expr.empty()) throw std::runtime_error("Empty expression");
    std::vector<Token> tokens = tokenize(expr);
    std::vector<Token> postfix = toPostfix(tokens);
    return buildASTFromPostfix(postfix, facts);
}

void buildRulesFromRuleSet(const RuleSet &ruleSet, std::unordered_map<char, FactNode*> &facts, std::vector<Rule> &rules) {

    size_t numRules = ruleSet.rules.size();
    for (const RuleString &ruleStr : ruleSet.rules) {
        try {
            ASTNode* condition = parseExpression(ruleStr.condition, facts);
            ASTNode* conclusion = parseExpression(ruleStr.conclusion, facts);

            std::string ruleText = ruleStr.condition + " " +
                                  (ruleStr.equalityType == IMPLICATION ? "=>" : "<=>") +
                                  " " + ruleStr.conclusion;
            rules.push_back(Rule(condition, conclusion, ruleStr.condition, ruleStr.conclusion));

            if (ruleStr.equalityType == BICONDITIONAL) {
                ASTNode* condCopy = parseExpression(ruleStr.condition, facts);
                ASTNode* concCopy = parseExpression(ruleStr.conclusion, facts);
                std::string reverseText = ruleStr.conclusion + " => " + ruleStr.condition;
                rules.push_back(Rule(concCopy, condCopy, ruleStr.conclusion, ruleStr.condition));
            }
        } catch (const std::exception &e) {
            std::cerr << "Error parsing rule '" << ruleStr.condition
                     << " => " << ruleStr.conclusion << "': " << e.what() << std::endl;
            throw;
        }
        rules.reserve(numRules * (ruleStr.equalityType == BICONDITIONAL ? 2 : 1));
    }
}

std::map<char, FactState> getAllLetters(const RuleSet &ruleSet) {

    std::map<char, FactState> mapLetter;
    for (const RuleString &rule : ruleSet.rules) {
        for (char c : rule.condition)
            if (std::isupper(c) && mapLetter.find(c) == mapLetter.end())
                mapLetter.insert({c, FactState::FALSE});
        for (char c : rule.conclusion)
            if (std::isupper(c) && mapLetter.find(c) == mapLetter.end())
                mapLetter.insert({c, FactState::FALSE});
    }
    for (char c : ruleSet.facts) {
        if (mapLetter.find(c) == mapLetter.end()) continue;
        mapLetter[c] = FactState::TRUE;
    }

    return mapLetter;
}

SimulationState buildASTNodes(const RuleSet &ruleSet) {

    std::unordered_map<char, FactNode*>	facts;
    std::vector<Rule>					rules;
    std::map<char, FactState>           mapLetter;

    mapLetter = getAllLetters(ruleSet);
    for (const auto &pair : mapLetter)
        facts[pair.first] = new FactNode(pair.first, pair.second);

    buildRulesFromRuleSet(ruleSet, facts, rules);
    return {facts, rules};
}

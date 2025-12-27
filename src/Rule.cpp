/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:36:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/27 15:52:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rule.hpp"
#include "Color.hpp"

Rule::Rule(ASTNode *condition, ASTNode *conclusion, const std::string &conditionString, const std::string &conclusionString)
{
	_condition = condition;
	_conclusion = conclusion;
	_conclusionString = conclusionString;
	_conditionString = conditionString;
	_getFacts(_conditionFacts, _condition);
	_getFacts(_conclusionFacts, _conclusion);
}

FactState	Rule::prove()
{
	FactState	res = _condition->prove();
	if (res == FactState::TRUE)
		std::cout << "Condition: " << this->_conditionString << " is TRUE" << std::endl;
	return (res);
}

void	Rule::_applyConclusion(ASTNode* node, FactState state, char c)
{
	ConditionNode	*cond = dynamic_cast<ConditionNode*>(node);
	FactNode	*fact = dynamic_cast<FactNode*>(node);

	if (fact)
	{
		if (state != FactState::UNDETERMINED)
			std::cout << "Fact " << fact->c << " proved to be " << state << std::endl;
		else
			std::cout << Color::Yellow << "Fact " << fact->c << " cannot be determined, set to " << state << Color::Reset << std::endl;
		if (_conclusionReturn != state && _conclusionReturn != FactState::UNDETERMINED)
			throw ContradictionError();
		_conclusionReturn = state;
		return ;
	}

	if (!cond)
		return ;

	if (cond->type == ConditionType::NOT)
		_applyConclusion(cond->left, FactState::FALSE, c);
	else if (cond->type == ConditionType::AND)
	{
		if (_hasFact(c, cond->left))
			_applyConclusion(cond->left, state, c);
		if (_hasFact(c, cond->right))
			_applyConclusion(cond->right, state, c);
	}
	else if (cond->type == ConditionType::OR || cond->type == ConditionType::XOR)
	{
		if (_hasFact(c, cond->left))
			_applyConclusion(cond->left, FactState::UNDETERMINED, c);
		if (_hasFact(c, cond->right))
			_applyConclusion(cond->right, FactState::UNDETERMINED, c);
	}
}

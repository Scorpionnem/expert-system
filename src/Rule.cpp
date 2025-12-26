/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:36:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/26 17:12:48 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rule.hpp"

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

FactState	Rule::_applyConclusion(ASTNode* node, FactState state, char c)
{
	ConditionNode	*cond = dynamic_cast<ConditionNode*>(node);
	FactNode	*fact = dynamic_cast<FactNode*>(node);

	if (fact)
	{
		std::cout << "Fact " << fact->c << " proved to be " << state << std::endl;
		if (fact->set && fact->state != state && fact->state != FactState::UNDETERMINED)
			std::cout << _conditionString << " CONTRADICTION, fact is set to " << fact->state << std::endl; // Need to set to undetermined, cant be resolved after contradiction is found
		return (state);
	}

	if (!cond)
		return (FactState::UNDETERMINED);

	if (cond->type == ConditionType::NOT)
		return (_applyConclusion(cond->left, FactState::FALSE, c));
	else if (cond->type == ConditionType::AND)
	{
		if (_hasFact(c, cond->left))
			return (_applyConclusion(cond->left, state, c));
		if (_hasFact(c, cond->right))
			return (_applyConclusion(cond->right, state, c));
	}
	return (FactState::UNDETERMINED);
}

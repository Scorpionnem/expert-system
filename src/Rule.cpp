/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:36:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 14:22:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rule.hpp"

Rule::Rule(ASTNode *condition, ASTNode *conclusion, const std::string &line)
{
	_condition = condition;
	_conclusion = conclusion;
	_line = line;
	_getFacts(_conditionFacts, _condition);
	_getFacts(_conclusionFacts, _conclusion);
}

FactState	Rule::compute()
{
	FactState	res = _condition->compute();
	if (res == FactState::TRUE)
		_applyConclusion(_conclusion, FactState::TRUE);
	return (res);
}

void	Rule::_applyConclusion(ASTNode* node, FactState state)
{
	ConditionNode	*cond = dynamic_cast<ConditionNode*>(node);
	FactNode	*fact = dynamic_cast<FactNode*>(node);

	if (fact)
	{
		std::cout << _line << " condition true, setting fact " << fact->c << " to " << state << std::endl;
		if (fact->set && fact->state != state && fact->state != FactState::UNDETERMINED)
			std::cout << _line << " CONTRADICTION, fact is set to " << fact->state << std::endl; // Need to set to undetermined, cant be resolved after contradiction is found
		fact->set = true;
		fact->state = state;
		return ;
	}

	if (!cond)
		return ;

	if (cond->type == ConditionType::NOT)
		_applyConclusion(cond->left, FactState::FALSE);
	else if (cond->type == ConditionType::AND)
	{
		_applyConclusion(cond->left, state);
		_applyConclusion(cond->right, state);
	}
	else if (cond->type == ConditionType::OR || cond->type == ConditionType::XOR)
	{
		FactNode	*l = dynamic_cast<FactNode*>(cond->left);
		FactNode	*r = dynamic_cast<FactNode*>(cond->right);

		if (l && l->state == FactState::FALSE)
			l->state = FactState::UNDETERMINED;
		if (r && r->state == FactState::FALSE)
			r->state = FactState::UNDETERMINED;
		if (!l)
			_applyConclusion(cond->left, FactState::UNDETERMINED);
		if (!r)
			_applyConclusion(cond->right, FactState::UNDETERMINED);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConditionNode.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:40:19 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/26 17:05:05 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConditionNode.hpp"

ConditionNode::ConditionNode(ConditionType type, ASTNode *left, ASTNode *right)
{
	this->left = left;
	this->right = right;
	this->type = type;
}

FactState	ConditionNode::prove()
{
	if (type == ConditionType::NOT)
	{
		FactState	a = left->prove();

		if (a == FactState::TRUE)
			return (FactState::FALSE);
		if (a == FactState::FALSE)
			return (FactState::TRUE);
		return (FactState::UNDETERMINED);
	}

	FactState	a = left->prove();
	FactState	b = right->prove();

	switch (type)
	{
		case ConditionType::AND:
		{
			if (a == FactState::FALSE || b == FactState::FALSE)
				return (FactState::FALSE);
			if (a == FactState::TRUE && b == FactState::TRUE)
				return (FactState::TRUE);
			return (FactState::UNDETERMINED);
		}
		case ConditionType::OR:
		{
			if (a == FactState::TRUE || b == FactState::TRUE)
				return (FactState::TRUE);
			if (a == FactState::FALSE && b == FactState::FALSE)
				return (FactState::FALSE);
			return (FactState::UNDETERMINED);
		}
		case ConditionType::XOR:
		{
			if (a != b
				&& (a == FactState::TRUE || a == FactState::FALSE)
				&& (b == FactState::TRUE || b == FactState::FALSE))
				return (FactState::TRUE);
			if (a == b
				&& (a == FactState::TRUE || a == FactState::FALSE)
				&& (b == FactState::TRUE || b == FactState::FALSE))
				return (FactState::FALSE);
			return (FactState::UNDETERMINED);
		}
		default:
			return (FactState::UNDETERMINED);
	}
}

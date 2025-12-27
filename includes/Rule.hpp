/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:34:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/27 15:44:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULE_HPP
# define RULE_HPP

# include <unordered_map>
# include "FactNode.hpp"
# include "ConditionNode.hpp"
# include <exception>

class	Rule
{
	public:
		class	ContradictionError : public std::exception {};
	public:
		Rule(ASTNode *condition, ASTNode *conclusion, const std::string &conditionString, const std::string &conclusionString);

		FactState	prove();
		bool		concludesFact(char fact)
		{
			return (_hasFact(fact, _conclusion));
		}
		FactState	applyConclusion(char fact)
		{
			_conclusionReturn = FactState::UNDETERMINED;
			try
			{
				_applyConclusion(_conclusion, FactState::TRUE, fact);
			} catch (const ContradictionError &e) {
				std::cout << "Contradiction error in " << _conclusionString << std::endl;
				return (FactState::UNDETERMINED);
			}
			return (_conclusionReturn);
		}
	// private:
		FactState	_conclusionReturn;
		void	_getFacts(std::unordered_map<char, FactNode*> &map, ASTNode *node)
		{
			ConditionNode	*cond = dynamic_cast<ConditionNode*>(node);
			FactNode		*fact = dynamic_cast<FactNode*>(node);

			if (cond)
			{
				_getFacts(map, cond->left);
				_getFacts(map, cond->right);
			}
			if (fact)
				map[fact->c] = fact;
		}
		bool	_hasFact(char c, ASTNode *node)
		{
			ConditionNode	*cond = dynamic_cast<ConditionNode*>(node);
			FactNode		*fact = dynamic_cast<FactNode*>(node);

			// if (cond && (cond->type == ConditionType::XOR || cond->type == ConditionType::OR))
			// 	return (false);
			if (cond)
			{
				if (_hasFact(c, cond->left))
					return (true);
				if (_hasFact(c, cond->right))
					return (true);
			}
			if (fact)
				return (fact->c == c);
			return (false);
		}
		ASTNode						*_condition;
		ASTNode						*_conclusion;
		std::unordered_map<char, FactNode*>	_conditionFacts;
		std::unordered_map<char, FactNode*>	_conclusionFacts;
		std::string	_conditionString;
		std::string	_conclusionString;
		void	_applyConclusion(ASTNode* node, FactState state, char fact);
};

#endif

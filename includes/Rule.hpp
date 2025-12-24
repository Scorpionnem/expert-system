/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:34:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 14:20:25 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULE_HPP
# define RULE_HPP

# include <unordered_map>
# include "FactNode.hpp"
# include "ConditionNode.hpp"

class	Rule
{
	public:
		Rule(ASTNode *condition, ASTNode *conclusion, const std::string &line = "unset");

		FactState	compute();
		bool		concludesFact(char fact)
		{
			return (_hasFact(fact, _conclusion));
		}
	//private:
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
		std::string	_line;
		void	_applyConclusion(ASTNode* node, FactState state);
};

#endif

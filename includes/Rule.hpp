/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:34:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 11:37:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULE_HPP
# define RULE_HPP

# include "FactNode.hpp"
# include "ConditionNode.hpp"

class	Rule
{
	public:
		Rule(ASTNode *condition, ASTNode *conclusion);

		FactState	compute();
	private:
		ASTNode	*_condition;
		ASTNode	*_conclusion;
		void	_applyConclusion(ASTNode* node, FactState state);
};

#endif

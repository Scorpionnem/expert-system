/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConditionNode.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:34:01 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 11:41:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONDITIONNODE_HPP
# define CONDITIONNODE_HPP

# include "ASTNode.hpp"
# include "ConditionType.hpp"

struct	ConditionNode : public ASTNode
{
	ASTNode			*left;
	ASTNode			*right;
	ConditionType	type;
	
	ConditionNode(ConditionType type, ASTNode *left, ASTNode *right);

	FactState	compute();
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactNode.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:33:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 13:52:24 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTNODE_HPP
# define FACTNODE_HPP

# include "ASTNode.hpp"

struct	FactNode : public ASTNode
{
	char		c;
	bool		set = false;
	FactState	state = FactState::FALSE;

	FactNode(char c, FactState state)
	{
		this->c = c;
		this->state = state;
	}
	FactState	compute()
	{
		return (state);
	}
};

#endif

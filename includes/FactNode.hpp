/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactNode.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:33:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/28 12:32:04 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTNODE_HPP
# define FACTNODE_HPP

# include "ASTNode.hpp"
# include <vector>

class Rule;

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
	FactState	prove();
	//Rules that contain this fact in its conclusion
	std::vector<Rule>	conclusions;
	//Rules that contain this fact in its condition
	std::vector<Rule>	conditions;
};

#endif

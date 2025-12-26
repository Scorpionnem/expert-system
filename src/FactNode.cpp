/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactNode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:41:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/26 16:42:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FactNode.hpp"
#include "parsing.hpp"

extern SimulationState	simState;
FactState	prove(SimulationState &simState, char fact);

FactState	FactNode::prove()
{
	return (::prove(simState, this->c));
}

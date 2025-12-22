/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactState.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:38:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 11:38:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FactState.hpp"

std::ostream& operator<<(std::ostream& os, const FactState& p)
{
	switch (p)
	{
		case FactState::FALSE:
			return (os << "FALSE");
		case FactState::TRUE:
			return (os << "TRUE");
		case FactState::UNDETERMINED:
			return (os << "UNDETERMINED");
	}
}

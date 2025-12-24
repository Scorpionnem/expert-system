/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConditionType.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 11:38:58 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConditionType.hpp"

std::ostream& operator<<(std::ostream& os, const ConditionType& p)
{
	switch (p)
	{
		case ConditionType::AND:
			return (os << "AND");
		case ConditionType::OR:
			return (os << "OR");
		case ConditionType::XOR:
			return (os << "XOR");
		case ConditionType::NOT:
			return (os << "NOT");
	}
	return (os);
}

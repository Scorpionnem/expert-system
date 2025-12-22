/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConditionType.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:32:44 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 11:38:57 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONDITIONTYPE_HPP
# define CONDITIONTYPE_HPP

# include <iostream>

enum class	ConditionType
{
	AND,
	OR,
	XOR,
	NOT,
};
std::ostream& operator<<(std::ostream& os, const ConditionType& p);

#endif

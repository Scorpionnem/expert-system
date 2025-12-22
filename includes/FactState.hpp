/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactState.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:32:01 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 11:38:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTSTATE_HPP
# define FACTSTATE_HPP

# include <iostream>

enum class	FactState
{
	FALSE,
	TRUE,
	UNDETERMINED
};
std::ostream& operator<<(std::ostream& os, const FactState& p);

#endif

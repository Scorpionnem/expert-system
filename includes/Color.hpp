/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:10:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/27 15:52:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_HPP
# define COLOR_HPP

namespace Color
{
	constexpr const char	*Red = "\e[0;31m";
	constexpr const char	*Green = "\e[0;32m";
	constexpr const char	*Blue = "\e[0;34m";
	constexpr const char	*Yellow = "\e[0;33m";
	constexpr const char	*Black = "\e[0;30m";
	constexpr const char	*Purple = "\e[0;35m";
	constexpr const char	*Cyan = "\e[0;36m";
	constexpr const char	*White = "\e[0;37m";

	constexpr const char	*Reset = "\e[0m";
};

#endif

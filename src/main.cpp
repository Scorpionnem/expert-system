/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/10 13:46:18 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

/*
	RULES:
		contient list de conditions et un resultat
		CONDITION (sous forme d'un arbre):
			contient soit une autre condition soit un char representant un fact ET la condition (AND, OR, XOR)
		RESULTAT:
			un fact
			FACT:
				char qui represente le fact et un bool pour son state

	exemple pour (A | B) & C => D
	
	RULE:
		CONDITION: ( (A | B) & C )
			CONDITION: (A | B)
				CONDITION: A
				CONDITION: B
			CONDITION: C
		RESULTAT:
			FACT:
				D -> true

	Quand on veux verifier une query (?D), on envoie la liste de facts que l'on connait a notre expert system, il passe dans toutes les rules et si a la fin D est true, on valide la query
*/

int	main(void)
{
	std::cout << "expert-system" << std::endl;
	return (0);
}

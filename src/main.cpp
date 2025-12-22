/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 11:37:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unordered_map>

#include "Rule.hpp"

int	main(void)
{
	std::unordered_map<char, ASTNode*>	facts;

	facts['A'] = new FactNode('A', FactState::TRUE);
	std::cout << "A\t:\t" <<  facts['A']->compute() << std::endl;
	facts['B'] = new FactNode('B', FactState::FALSE);
	std::cout << "B\t:\t" <<  facts['B']->compute() << std::endl;
	facts['C'] = new FactNode('C', FactState::FALSE);
	std::cout << "C\t:\t" <<  facts['C']->compute() << std::endl;
	facts['D'] = new FactNode('D', FactState::FALSE);
	std::cout << "D\t:\t" <<  facts['D']->compute() << std::endl;

	ASTNode	*A_OR_B = new ConditionNode(ConditionType::OR, facts['A'], facts['B']);
	ASTNode	*C_AND_D = new ConditionNode(ConditionType::AND, facts['C'], facts['D']);

	Rule	rule(A_OR_B, C_AND_D);

	std::cout << std::endl;
	std::cout << "A_OR_B\t:\t" << rule.compute() << std::endl;
	std::cout << std::endl;

	std::cout << "C\t:\t" <<  facts['C']->compute() << std::endl;
	std::cout << "D\t:\t" <<  facts['D']->compute() << std::endl;
}

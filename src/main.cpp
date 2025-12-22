/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 14:55:16 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

#include "Rule.hpp"

std::unordered_map<char, FactNode*>	facts;
std::vector<Rule>					rules;

void	prove(char fact)
{
	FactState	state = facts[fact]->state;
	std::cout << "Proving " << fact << " wich is " << state << std::endl;
	if (state == FactState::TRUE)
		return ;
	for (Rule &rule : rules)
	{
		if (rule._hasFact(fact, rule._conclusion))
		{
			for (auto fact : rule._conditionFacts)
				prove(fact.first);
			rule.compute();
		}
	}
}

int	main(void)
{
	facts['A'] = new FactNode('A', FactState::TRUE);
	facts['B'] = new FactNode('B', FactState::FALSE);
	facts['C'] = new FactNode('C', FactState::FALSE);
	facts['D'] = new FactNode('D', FactState::FALSE);

	ConditionNode	*C_OR_B = new ConditionNode(ConditionType::OR, facts['C'], facts['B']);(void)C_OR_B;

	rules.push_back(Rule(facts['A'], facts['B'], "A => B"));
	rules.push_back(Rule(facts['B'], facts['D'], "B => D"));

	prove('D');
	std::cout << "D\t:\t" <<  facts['D']->state << std::endl;
}

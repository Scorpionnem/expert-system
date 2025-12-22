/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/22 15:17:10 by mbatty           ###   ########.fr       */
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

#include <fstream>

void	preprocessLine(std::string &line)
{
	line = line.substr(0, line.find('#'));
}

void	readFile(const std::string &path)
{
	std::ifstream	file(path);

	if (!file.is_open())
		return ;
	std::string	line;
	while (getline(file, line))
	{
		preprocessLine(line);

		if (line.empty())
			continue ;
		std::cout << line << std::endl;
	}
}

int	main(void)
{
	readFile("example.txt");
	std::cout << std::endl;
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

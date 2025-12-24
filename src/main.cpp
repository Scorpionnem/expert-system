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
#include <algorithm>
#include "parsing.hpp"
#include "debug.hpp"

#include "Rule.hpp"

void	prove(SimulationState &simState, char fact)
{
	FactState	state = simState.facts[fact]->state;
	if (state == FactState::TRUE)
		return ;
	for (Rule &rule : simState.rules)
	{
		if (rule._hasFact(fact, rule._conclusion))
		{
			for (auto fact : rule._conditionFacts)
				prove(simState, fact.first);
			rule.compute();
		}
	}
}

#include <fstream>

std::vector<std::string>	readFile(const std::string &path)
{
	std::ifstream	file(path);
	std::vector<std::string> lines;

	if (!file.is_open()) return {};

	std::string	line;
	while (getline(file, line))
	{
		preprocessLine(line);
		if (line.empty()) continue ;
		lines.push_back(line);
	}
	return lines;
}

int	main(int ac, char **av)
{
	if (ac > 3)
	{
		std::cerr << "Usage: " << av[0] << " [Facts] [Querry]" << std::endl;
		return (1);
	}
	try {
		RuleSet ruleSet;
		SimulationState simState;
		std::vector<std::string> lines = readFile("example.txt");
		ruleSet = parse(lines, ac, av);
		simState = buildASTNodes(ruleSet);
		for (const char &q : ruleSet.querry) {
			prove(simState, q);
			std::cout << q << " : " <<  simState.facts[q]->state << std::endl;
		}
		cleanupCreatedNodes();
		for (auto &pair : simState.facts) delete pair.second;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

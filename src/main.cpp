/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/26 17:27:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include "parsing.hpp"
#include "debug.hpp"

#include "Rule.hpp"

std::map<char, bool>	checkedFacts;
SimulationState			simState;

FactState	prove(SimulationState &simState, char fact)
{
	FactState	state = simState.facts[fact]->state;

	if (state == FactState::TRUE || checkedFacts[fact])
	{
		std::cout << "Fact " << fact << " is know to be " << state;
		return (state);
	}
	checkedFacts[fact] = true;

	uint		provedRules = 0;
	FactState	res = FactState::UNDETERMINED;
	for (Rule &rule : simState.rules)
	{
		if (rule._hasFact(fact, rule._conclusion))
		{
			std::cout << "Proving " << rule._conditionString << " => " << rule._conclusionString << std::endl;
			if (rule.prove() == FactState::TRUE)
			{
				FactState	conclusion = rule._applyConclusion(rule._conclusion, FactState::TRUE, fact);

				if (conclusion != res && res != FactState::UNDETERMINED)
				{
					std::cout << "CONTRADICTION ERROR" << std::endl;
					return (FactState::UNDETERMINED);
				}
				res = conclusion;
				provedRules++;
			}
			std::cout << std::endl;
		}
	}
	if (provedRules == 0)
		std::cout << "No rules were able to prove " << fact << std::endl;
	return (res);
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
	if (ac > 4 || ac < 2)
	{
		std::cerr << "Usage: " << av[0] << " [File] [Facts] [Querry]" << std::endl;
		return (1);
	}
	try {
		RuleSet ruleSet;
		std::vector<std::string> lines = readFile(av[1]);
		ruleSet = parse(lines, ac, av);
		simState = buildASTNodes(ruleSet);
		for (const char &q : ruleSet.querry) {
			checkedFacts.clear();
			FactState	res = prove(simState, q);
			std::cout << q << " : " <<  res << std::endl;
		}
		cleanupCreatedNodes();
		for (auto &pair : simState.facts) delete pair.second;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

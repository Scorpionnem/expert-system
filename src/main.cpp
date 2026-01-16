/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/16 12:31:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include "parsing.hpp"
#include "debug.hpp"
#include "Rule.hpp"
#include "Color.hpp"

std::map<char, bool>	checkedFacts;
SimulationState			simState;

FactState	prove(SimulationState &simState, char fact)
{
	FactState	state = simState.facts[fact]->state;

	if (state == FactState::TRUE)
	{
		std::cout << "Fact " << fact << " is know to be " << state << std::endl;
		return (state);
	}
	if (checkedFacts[fact])
	{
		std::cout << Color::Yellow << "Cycle detected on " << fact << Color::Reset << std::endl;
		return (FactState::UNDETERMINED);
	}
	checkedFacts[fact] = true;
	
	std::cout << "Trying to prove " << fact << std::endl;

	uint		provedRules = 0;
	FactState	res = FactState::UNDETERMINED;
	for (Rule &rule : simState.rules)
	{
		if (rule._hasFact(fact, rule._conclusion))
		{
			std::cout << "Proving: " << rule._conditionString << " => " << rule._conclusionString << std::endl;
			FactState	ruleRes = rule.prove();
			std::cout << "Proved: " << rule._conditionString << " is " << ruleRes << std::endl;
			if (ruleRes == FactState::TRUE)
			{
				FactState	conclusion = rule.applyConclusion(fact);

				if (conclusion != res && res != FactState::UNDETERMINED)
				{
					std::cout << Color::Red <<  "Contradiction error between rules" << Color::Reset << std::endl;
					return (FactState::UNDETERMINED);
				}
				res = conclusion;
				provedRules++;
			}
			else
				std::cout << "Cannot set conclusion: " << rule._conclusionString << std::endl;
		}
	}
	if (provedRules == 0)
	{
		std::cout << "No rules were able to prove " << fact << std::endl;
		checkedFacts[fact] = false;
		return (state);
	}
	checkedFacts[fact] = false;
	return (res);
}

void	linkFactsRules(SimulationState &simState)
{
	for (auto &pair : simState.facts)
	{
		FactNode	*fact = pair.second;
		for (Rule &rule : simState.rules)
		{
			if (rule._hasFact(fact->c, rule._conclusion))
				fact->conclusions.push_back(rule);
			if (rule._hasFact(fact->c, rule._condition))
				fact->conditions.push_back(rule);
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
		linkFactsRules(simState);

		printAllFacts(simState.facts);
		std::cout << std::endl;
		printAllRules(simState.rules);
		std::cout << std::endl;

		bool	first = true;
		for (const char &q : ruleSet.querry)
		{
			if (!first)
				std::cout << std::endl;
			first = false;

			checkedFacts.clear();
			FactState	res = prove(simState, q);

			if (res == FactState::TRUE)
				std::cout << Color::Green;
			if (res == FactState::FALSE)
				std::cout << Color::Red;
			if (res == FactState::UNDETERMINED)
				std::cout << Color::Yellow;

			std::cout << std::endl << q << " : " <<  res << Color::Reset << std::endl;
		}
		cleanupCreatedNodes();
		for (auto &pair : simState.facts) delete pair.second;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

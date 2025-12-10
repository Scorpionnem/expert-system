/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/10 14:48:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>

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

struct	Fact
{
	Fact(char c, bool state)
	{
		this->c = c;
		this->state = state;
	}
	char	c;
	bool	state = false;
};

enum class	ConditionType
{
	AND,
	OR,
	FACT, // Returns if condition's fact is true
};

class	ComputingError: public std::exception
{
	public:
		ComputingError(): _msg("Computing error") {}
		ComputingError(const std::string &msg): ComputingError()
		{
			_msg += " ";
			_msg += msg;
		}
		virtual const char*	what() const throw()
		{
			return (_msg.c_str());
		}
	private:
		std::string	_msg;
};

struct	Condition
{
	struct Condition	*left;
	struct Condition	*right;
	Fact				*fact;
	ConditionType		type;

	Condition(ConditionType type, struct Condition *left, struct Condition *right, Fact *fact)
	{
		this->type = type;
		this->left = left;
		this->right = right;
		this->fact = fact;
	}
	bool	compute()
	{
		if (type == ConditionType::FACT)
			return (fact->state);
		if (type == ConditionType::AND)
			return (left->compute() && right->compute());
		if (type == ConditionType::OR)
			return (left->compute() || right->compute());
		throw ComputingError("ConditionType not found");
	}
};

struct	Rule
{
	Rule(Condition *condition)
	{
		this->condition = condition;
	}
	Condition	*condition;
	bool	compute()
	{
		return (condition->compute());
	}
};

int	main(void)
{
	{
		// (A | B) & C => D
		Fact	A('A', true);
		Fact	B('B', false);
		Fact	C('C', true);
	
		Condition	A_EXISTS(ConditionType::FACT, NULL, NULL, &A);
		Condition	B_EXISTS(ConditionType::FACT, NULL, NULL, &B);
		Condition	C_EXISTS(ConditionType::FACT, NULL, NULL, &C);
	
		Condition	A_OR_B(ConditionType::OR, &A_EXISTS, &B_EXISTS, NULL);
		Condition	A_OR_B_AND_C(ConditionType::AND, &A_OR_B, &C_EXISTS, NULL);
	
		Rule	rule(&A_OR_B_AND_C);
	
		Fact	D('D', rule.compute());
		std::cout << "(A | B) & C => D is: " << D.state << std::endl;
	}

	{
		// A & B & C => D -> transforme en: (A & B) & C
		// Il faut transformer avec des parentheses car fonctionne que par bloc de 2
		// (Pas sur que ce soit valide sur le long terme mais c'est la solution a la quelle j'ai pense sur le moment)
		Fact	A('A', true);
		Fact	B('B', true);
		Fact	C('C', true);

		Condition	A_EXISTS(ConditionType::FACT, NULL, NULL, &A);
		Condition	B_EXISTS(ConditionType::FACT, NULL, NULL, &B);
		Condition	C_EXISTS(ConditionType::FACT, NULL, NULL, &C);

		Condition	A_AND_B(ConditionType::AND, &A_EXISTS, &B_EXISTS, NULL);
		Condition	A_AND_B_AND_C(ConditionType::AND, &A_AND_B, &C_EXISTS, NULL);

		Rule	rule(&A_AND_B_AND_C);
	
		Fact	D('D', rule.compute());
		std::cout << "A & B & C => D is: " << D.state << std::endl;
	}
	std::cout << "expert-system" << std::endl;
	return (0);
}

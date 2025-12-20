/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/20 14:52:37 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

enum class	FactState
{
	FALSE,
	TRUE,
	UNDETERMINED
};
std::ostream& operator<<(std::ostream& os, const FactState& p)
{
	switch (p)
	{
		case FactState::FALSE:
			return (os << "FALSE");
		case FactState::TRUE:
			return (os << "TRUE");
		case FactState::UNDETERMINED:
			return (os << "UNDETERMINED");
	}
}

enum class	ConditionType
{
	AND,
	OR,
	XOR,
	NOT,
};
std::ostream& operator<<(std::ostream& os, const ConditionType& p)
{
	switch (p)
	{
		case ConditionType::AND:
			return (os << "AND");
		case ConditionType::OR:
			return (os << "OR");
		case ConditionType::XOR:
			return (os << "XOR");
		case ConditionType::NOT:
			return (os << "NOT");
	}
}

struct	ASTNode
{
	virtual ~ASTNode() {}
	virtual FactState	compute() = 0;
};

struct	FactNode : public ASTNode
{
	char		c;
	FactState	state = FactState::FALSE;

	FactNode(char c, FactState state)
	{
		this->c = c;
		this->state = state;
	}
	FactState	compute()
	{
		return (state);
	}
};

struct	ConditionNode : public ASTNode
{
	ASTNode			*left;
	ASTNode			*right;
	ConditionType	type;
	
	ConditionNode(ConditionType type, ASTNode *left, ASTNode *right = NULL)
	{
		this->left = left;
		this->right = right;
		this->type = type;
	}

	FactState	compute()
	{
		if (type == ConditionType::NOT)
			return (left->compute() == FactState::FALSE ? FactState::TRUE : FactState::FALSE);

		FactState	a = left->compute();
		FactState	b = right->compute();

		switch (type)
		{
			case ConditionType::AND:
				return (a == FactState::TRUE && b == FactState::TRUE ? FactState::TRUE : FactState::FALSE);
			case ConditionType::OR:
				return (a == FactState::TRUE || b == FactState::TRUE ? FactState::TRUE : FactState::FALSE);
			case ConditionType::XOR:
				return (a != b ? FactState::TRUE : FactState::FALSE);
			default:
				return (FactState::UNDETERMINED);
		}
	}
};

int	main(void)
{
	std::unordered_map<char, ASTNode*>	facts;

	facts['A'] = new FactNode('A', FactState::FALSE);
	std::cout << "A\t:\t" <<  facts['A']->compute() << std::endl;
	facts['B'] = new FactNode('B', FactState::FALSE);
	std::cout << "B\t:\t" <<  facts['B']->compute() << std::endl;

	ASTNode	*A_OR_B = new ConditionNode(ConditionType::OR, facts['A'], facts['B']);
	std::cout << "A | B\t:\t" << A_OR_B->compute() << std::endl;

	ASTNode	*A_XOR_B = new ConditionNode(ConditionType::XOR, facts['A'], facts['B']);
	std::cout << "A ^ B\t:\t" << A_XOR_B->compute() << std::endl;

	ASTNode	*NOT_A = new ConditionNode(ConditionType::NOT, facts['A']);
	std::cout << "!A\t:\t" << NOT_A->compute() << std::endl;

	ASTNode	*NOT_A_XOR_B = new ConditionNode(ConditionType::XOR, NOT_A, facts['B']);
	std::cout << "!A ^ B\t:\t" << NOT_A_XOR_B->compute() << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:26:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/20 14:29:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>

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
		FactState	b = left->compute();

		switch (type)
		{
			case ConditionType::AND:
				return (a == FactState::TRUE && b == FactState::TRUE ? FactState::TRUE : FactState::FALSE);
			case ConditionType::OR:
				return (a == FactState::TRUE || b == FactState::TRUE ? FactState::TRUE : FactState::FALSE);
			default:
				return (FactState::UNDETERMINED);
		}

		return (FactState::UNDETERMINED);
	}
};

int	main(void)
{
	ASTNode	*A = new FactNode('A', FactState::FALSE);
	ASTNode	*B = new FactNode('B', FactState::FALSE);

	ASTNode	*A_OR_B = new ConditionNode(ConditionType::OR, A, B);

	std::cout << A_OR_B->compute() << std::endl;

	ASTNode	*NOT_A = new ConditionNode(ConditionType::NOT, A);
	std::cout << NOT_A->compute() << std::endl;
}

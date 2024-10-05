/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:01:16 by mhugueno          #+#    #+#             */
/*   Updated: 2024/05/04 17:26:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"
#include "node.hpp"

void	aStar(node& game)
{
	size_t	timeComplexity = 0;
	size_t	sizeComplexity = 0;
	std::unordered_set<node*, NodeHash, NodeEqual>	openL;
	std::unordered_set<node*, NodeHash, NodeEqual>	closeL;
	std::priority_queue<node*, std::vector<node*>, CompareNode> openLQ;
	game.print(game.getArray());
	node* bestNode = &game;
	while (!bestNode->didWeWon())
	{
		for (int i = 0; i < 4; i++)
		{
			node* tmp = new node(*bestNode);
			if (tmp->moveByIndex(i, tmp->getLastMove()))
			{
				tmp->setG(bestNode->getG() + 1);
				tmp->calcF();
				auto itO = openL.find(tmp), itL = closeL.find(tmp);
				if (itO != openL.end() || itL != closeL.end())
					delete(tmp);
				else
				{
					tmp->addPrevious(bestNode);
					openLQ.push(tmp);
					openL.insert(tmp);
				}
			}
			else
				delete (tmp);
		}
		if (!openLQ.empty())
		{
			bestNode = openLQ.top();
			closeL.insert(bestNode);
			openL.erase(bestNode);
			openLQ.pop();
			std::cout << "\rIteration : " << timeComplexity << " | g(n) : " << bestNode->getG() << " | f(n) : " << bestNode->getF() << std::flush;
			timeComplexity++;
		}
		else
		{
			std::cout << "OpenL is empty." << std::endl;
			return;
		}
		if ((openL.size() + closeL.size()) > sizeComplexity)
			sizeComplexity = (openL.size() + closeL.size());
	}

	if (bestNode->didWeWon())
	{
		int	moveN = (bestNode->getPrevious().size());
		for (size_t i = 0; i < bestNode->getPrevious().size(); i++)
		{
			std::cout << std::endl << "Move : " << bestNode->getPrevious()[i]->getLastMove() << std::endl;
			bestNode->getPrevious()[i]->print(bestNode->getPrevious()[i]->getArray());
		}
		std::cout << std::endl << "Move : " << bestNode->getLastMove() << std::endl;
		bestNode->print(bestNode->getArray());
		congratulation(timeComplexity, sizeComplexity, moveN);
	}
}

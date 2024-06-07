/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:03:24 by mhugueno          #+#    #+#             */
/*   Updated: 2024/05/04 17:24:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "lib.hpp"

class node
{
	public:
		node(std::string mode, std::string heuristic);
		node(const node& other);
		virtual	~node();

		int**	getArray()			const;
		int		getX()				const;
		int**	getTargetNode()		const;
		int**	getStartNode()		const;
		int		getF()				const;
		int		getG()				const;
		std::string	getLastMove()	const;
		std::vector<node*>	getPrevious()	const;
		std::string	getMode()		const;
		std::string	getHeuristic()	const;

		void	setG(int value);
		void	addPrevious(node* previous);

		void	deleteArray();
		void	setUp(int value);
		void	randomise();
		void	parse(std::string value);
		void	print(int** array);
		void	calcTargetNode();
		void	calcStartNode();
		bool	moveUp();
		bool	moveDown();
		bool	moveLeft();
		bool	moveRight();
		bool	moveByIndex(int index, std::string lastMove);
		bool	isItEqual(int** array);
		bool	didWeWon();
		void	calcF();
		void	setUpReverse();

	private:
		int			**array;
		int			size_x;
		int			**startNode;
		int			**targetNode;
		int			f;
		int			g;
		std::string	lastMove;
		std::vector<node*>	previous;
		std::string	mode;
		std::string	heuristic;
};

struct CompareNode
{
	bool operator()(const node* a, const node* b) const
	{
		return (a->getF() > b->getF());
	}
};

struct NodeHash
{
	std::size_t operator()(const node* n) const
	{
		std::size_t h = 0;
		std::hash<int> hasher;
		for (int i = 0; i < n->getX(); i++)
		{
			for (int j = 0; j < n->getX(); j++)
			{
				h = h * 31 + hasher(n->getArray()[i][j]);
			}
		}
		return h;
	}
};

struct NodeEqual
{
	bool operator()(const node* lhs, const node* rhs) const
	{
		for (int i = 0; i < lhs->getX(); i++)
		{
			for (int j = 0; j < lhs->getX(); j++)
			{
				if (lhs->getArray()[i][j] != rhs->getArray()[i][j])
					return (false);
			}
		}
		return (true);
	}
};

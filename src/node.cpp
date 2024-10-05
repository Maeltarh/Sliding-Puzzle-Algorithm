/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:26:40 by mhugueno          #+#    #+#             */
/*   Updated: 2024/05/04 17:28:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.hpp"

node::node(std::string mode, std::string heuristic) : g(0), mode(mode), heuristic(heuristic)
{

}

node::node(const node& other)
{
	this->mode = other.mode;
	this->size_x = other.size_x;
	this->array = new int*[this->size_x];
	this->heuristic = other.heuristic;
	for (int i = 0; i < this->size_x; i++)
	{
		this->array[i] = new int[this->size_x];
		for (int j = 0; j < this->size_x; j++)
		{
			this->array[i][j] = other.array[i][j];
		}
	}
	this->startNode = new int*[this->size_x];
	for (int i = 0; i < this->size_x; i++)
	{
		this->startNode[i] = new int[this->size_x];
		for (int j = 0; j < this->size_x; j++)
		{
			this->startNode[i][j] = other.array[i][j];
		}
	}
	this->targetNode = new int*[this->size_x];
	for (int i = 0; i < this->size_x; i++)
	{
		this->targetNode[i] = new int[this->size_x];
		for (int j = 0; j < this->size_x; j++)
		{
			this->targetNode[i][j] = other.targetNode[i][j];
		}
	}
	for (size_t i = 0; i < other.previous.size(); i++)
	{
		this->previous.push_back(other.previous[i]);
	}
}

node::~node()
{
	for (int i = 0; i < this->size_x; i++)
	{
		delete	(this->array[i]);
	}
	delete	(this->array);
	if (this->targetNode)
	{
		for (int i = 0; i < this->size_x; i++)
		{
			delete	(this->targetNode[i]);
		}
		delete	(this->targetNode);
		for (int i = 0; i < this->size_x; i++)
		{
			delete	(this->startNode[i]);
		}
		delete	(this->startNode);
	}
}

int**	node::getArray()	const
{
	return	(this->array);
}

int	node::getX()	const
{
	return	(this->size_x);
}

int**	node::getTargetNode()	const
{
	return	(this->targetNode);
}

int**	node::getStartNode()	const
{
	return	(this->startNode);
}

int	node::getF()	const
{
	return (this->f);
}

int	node::getG()	const
{
	return (this->g);
}

std::string	node::getLastMove()	const
{
	return (this->lastMove);
}

std::vector<node*>	node::getPrevious()	const
{
	return (this->previous);
}

std::string	node::getMode()	const
{
	return (this->mode);
}

std::string	node::getHeuristic()	const
{
	return (this->heuristic);
}

void	node::setG(int value)
{
	this->g = value;
}

void	node::addPrevious(node* previous)
{
	this->previous.push_back(previous);
}

void	node::deleteArray()
{
	for (int i = 0; i < this->size_x; i++)
	{
		delete	(this->array[i]);
	}
	delete	(this->array);
}

void	node::setUp(int value)
{
	this->size_x = value;
	this->array = new int*[this->size_x];
	for (int x = 0; x < this->size_x; x++)
	{
		this->array[x] = new int[this->size_x];
		for (int y = 0; y < this->size_x; y++)
			this->array[x][y] = -1;
	}
}

void	node::randomise()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, ((this->size_x * this->size_x) - 1));

	int	randomValue = dist(gen);
	for (int i = 0; i < this->size_x; i++)
	{
		for (int y = 0; y < this->size_x; y++)
		{
			while (isInArray(this->array, i, this->size_x, randomValue) != 0)
			{
				randomValue = dist(gen);
			}
			this->array[i][y] = randomValue;
		}
	}
}

void	node::parse(std::string value)
{
	size_t i = 0;
	for (i = 0; i < value.length(); i++)
	{
		if (value[i] == '\n' || value[i] == 10)
		{
			if (value[i + 1] >= 48 && value[i + 1] <= 57)
			{
				this->size_x = atoi(&value[i + 1]);
				break;
			}
		}
	}
	this->array = new int*[this->size_x];
	for (int x = 0; x < this->size_x; x++)
	{
		this->array[x] = new int[this->size_x];
	}
	int y = 0;
	int yy = 0;
	std::string tmp;
	for (size_t x = i + 2; x < value.length(); x++)
	{
		if (value[x] >= 48 && value[x] <= 57)
		{
			tmp.clear();
			while (value[x] >= 48 && value[x] <= 57)
			{
				tmp.push_back(value[x]);
				x++;
			}
			this->array[y][yy] = atoi(tmp.c_str());
			yy++;
		}
		if (yy >= this->size_x)
		{
			yy = 0;
			y++;
		}
		if (y == this->size_x)
			break;
	}
}

void	node::print(int** array)
{
	for (int i = 0; i < this->size_x; i++)
	{
		for (int y = 0; y < this->size_x; y++)
		{
			std::cout << array[i][y];
			if (array[i][y] < 10)
				std::cout << "  ";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void	node::calcTargetNode()
{
	int	count = 1;
	this->targetNode = new int*[this->size_x];
	for (int i = 0; i < this->size_x; i++)
	{
		this->targetNode[i] = new int[this->size_x];
		for (int y = 0; y < this->size_x; y++)
		{
			if (count == (this->size_x * this->size_x))
				count = 0;
			this->targetNode[i][y] = count;
			count++;
		}
	}
}

void	node::calcStartNode()
{
	this->startNode = new int*[this->size_x];
	for (int i = 0; i < this->size_x; i++)
	{
		this->startNode[i] = new int[this->size_x];
		for (int y = 0; y < this->size_x; y++)
		{
			this->startNode[i][y] = this->array[i][y];
		}
	}
}

bool	node::moveUp()
{
	bool toggle = false;
	int i = 0;
	int y = 0;
	for (i = 0; i < this->size_x; i++)
	{
		for (y = 0; y < this->size_x; y++)
		{
			if (this->array[i][y] == 0)
			{
				toggle = true;
				break;
			}
		}
		if (toggle == true)
			break;
	}
	if (i == 0)
		return (false);
	this->array[i][y] = this->array[i - 1][y];
	this->array[i - 1][y] = 0;
	return (true);
}

bool	node::moveDown()
{
	bool toggle = false;
	int i = 0;
	int y = 0;
	for (i = 0; i < this->size_x; i++)
	{
		for (y = 0; y < this->size_x; y++)
		{
			if (this->array[i][y] == 0)
			{
				toggle = true;
				break;
			}
		}
		if (toggle == true)
			break;
	}
	if (i >= this->size_x - 1)
		return (false);
	this->array[i][y] = this->array[i + 1][y];
	this->array[i + 1][y] = 0;
	return (true);
}

bool	node::moveLeft()
{
	bool toggle = false;
	int i = 0;
	int y = 0;
	for (i = 0; i < this->size_x; i++)
	{
		for (y = 0; y < this->size_x; y++)
		{
			if (this->array[i][y] == 0)
			{
				toggle = true;
				break;
			}
		}
		if (toggle == true)
			break;
	}
	if (y == 0)
		return (false);
	this->array[i][y] = this->array[i][y - 1];
	this->array[i][y - 1] = 0;
	return (true);
}

bool	node::moveRight()
{
	bool toggle = false;
	int i = 0;
	int y = 0;
	for (i = 0; i < this->size_x; i++)
	{
		for (y = 0; y < this->size_x; y++)
		{
			if (this->array[i][y] == 0)
			{
				toggle = true;
				break;
			}
		}
		if (toggle == true)
			break;
	}
	if (y >= this->size_x - 1)
		return (false);
	this->array[i][y] = this->array[i][y + 1];
	this->array[i][y + 1] = 0;
	return (true);
}

bool	node::moveByIndex(int index, std::string lastMove)
{
	switch(index)
	{
		case 0:
			if (lastMove != "down")
			{
				this->lastMove = "up";
				return (moveUp());
			}
			break;
		case 1:
			if (lastMove != "up")
			{
				this->lastMove = "down";
				return (moveDown());
			}
			break;
		case 2:
			if (lastMove != "right")
			{
				this->lastMove = "left";
				return (moveLeft());
			}
			break;
		case 3:
			if (lastMove != "left")
			{
				this->lastMove = "right";
				return (moveRight());
			}
			break;
		default:
			std::cerr << "Invalid index!" << std::endl;
			return (false);
			break;
	}
	return (false);
}

bool	node::isItEqual(int** array)
{
	for (int i = 0; i < this->size_x; i++)
	{
		for (int j = 0; j < this->size_x; j++)
		{
			if (array[i][j] != this->array[i][j])
				return (false);
		}
	}
	return (true);
}

bool	node::didWeWon()
{
	for (int i = 0; i < this->size_x; i++)
	{
		for (int j = 0; j < this->size_x; j++)
		{
			if (this->array[i][j] != this->targetNode[i][j])
				return (false);
		}
	}
	return (true);
}

void	node::calcF()
{
	int	index = 0;
	std::string	mode[] = {"default", "uniform", "greedy"};
	int modeSize = sizeof(mode) / sizeof(mode[0]);
	while (mode[index] != this->mode)
	{
		index++;
		if (index >= modeSize)
		{
			std::cout << "Error: wrong search argument." << std::endl;
			exit (1);
		}
	}
	int h;
	if (this->heuristic != "none")
	{
		std::map<std::string, std::function<int(int**, int)>> fonctionMap = {
			{"manhattanDistance", manhattanDistance},
			{"rowColCheck", rowColCheck},
			{"linearConflict", linearConflict},
			{"cornerTiles", cornerTiles},
			{"adjacentTiles", adjacentTiles},
			{"invertedPairs", invertedPairs},
			{"distantTiles", distantTiles},
			{"edgeTiles", edgeTiles},
			{"isolatedTiles", isolatedTiles}
		};
		fonctionMap[this->heuristic](this->array, this->size_x);
	}
	else
	{
		if (this->size_x <= 6)
		{
			h = ((manhattanDistance(this->array, this->size_x) * 2) + (rowColCheck(this->array, this->size_x))
				+ (linearConflict(this->array, this->size_x)) + (cornerTiles(this->array, this->size_x))
				+ (adjacentTiles(this->array, this->size_x)) + (invertedPairs(this->array, this->size_x))
				+ (distantTiles(this->array, this->size_x) * 3) + (edgeTiles(this->array, this->size_x))
				+ (isolatedTiles(this->array, this->size_x)));
		}
		else
		{
			h = ((manhattanDistance(this->array, this->size_x)) + rowColCheck(this->array, this->size_x)
				+ linearConflict(this->array, this->size_x) + cornerTiles(this->array, this->size_x)
				+ adjacentTiles(this->array, this->size_x) + invertedPairs(this->array, this->size_x)
				+ (distantTiles(this->array, this->size_x) * 2));
		}
	}
	switch(index)
	{
		case 0:
			this->f = (this->g / 2) + h;
			break;
		case 1:
			this->f = this->g;
			break;
		case 2:
			this->f = h;
			break;
		default:
			exit (0);
			break;
	}
}

void	node::setUpReverse()
{
	for (int i = 0; i < this->size_x; i++)
	{
		for (int j = 0; j < this->size_x; j++)
		{
			this->targetNode[i][j] = this->array[i][j];
		}
	}
	int count = 1;
	for (int i = 0; i < this->size_x; i++)
	{
		for (int y = 0; y < this->size_x; y++)
		{
			if (count == (this->size_x * this->size_x))
				count = 0;
			this->array[i][y] = count;
			count++;
		}
	}
}

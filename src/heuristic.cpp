/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:28:24 by marvin            #+#    #+#             */
/*   Updated: 2023/11/02 13:28:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"
#include "node.hpp"

int	manhattanDistance(int** array, int size_x)
{
	int value = 0;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			int tile = array[i][j];
			if (tile == 0)
				continue;
			int target_i = (tile - 1) / size_x;
			int target_j = (tile - 1) % size_x;

			value += std::abs(i - target_i) + std::abs(j - target_j);
		}
	}
	return (value);
}

int	rowColCheck(int** array, int size_x)
{
	int value = 0;
	for (int j = 0; j < size_x; j++)
	{
		int maxRow = -1;
		for (int i = 0; i < size_x; i++)
		{
			if (array[i][j] != 0 && (array[i][j] - 1) % size_x == j)
			{
				if (array[i][j] < maxRow)
					value += 2;
				else
					maxRow = array[i][j];
			}
		}
	}
	for (int i = 0; i < size_x; i++)
	{
		int maxCol = -1;
		for (int j = 0; j < size_x; j++)
		{
			if (array[i][j] != 0 && (array[i][j] - 1) / size_x == i)
			{
				if (array[i][j] < maxCol)
					value += 2;
				else
					maxCol = array[i][j];
			}
		}
	}
	return (value);
}

int linearConflict(int** array, int size_x)
{
	int conflicts = 0;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x - 1; j++)
		{
			if (array[i][j] != 0 && (array[i][j] - 1) / size_x == i)
			{
				for (int k = j + 1; k < size_x; k++)
				{
					if (array[i][k] != 0 && (array[i][k] - 1) / size_x == i && array[i][j] > array[i][k])
						conflicts++;
				}
			}
		}
	}
	for (int j = 0; j < size_x; j++)
	{
		for (int i = 0; i < size_x - 1; i++)
		{
			if (array[i][j] != 0 && (array[i][j] - 1) % size_x == j)
			{
				for (int k = i + 1; k < size_x; k++)
				{
					if (array[k][j] != 0 && (array[k][j] - 1) % size_x == j && array[i][j] > array[k][j])
						conflicts++;
					}
				}
			}
	}
	return (conflicts * 2);
}

int cornerTiles(int** array, int size_x)
{
	int cornerPenalty = 0;
	if (array[0][0] != 1)
		cornerPenalty += 3;
	if (array[0][size_x - 1] != size_x)
		cornerPenalty += 3;
	if (array[size_x - 1][0] != size_x * (size_x - 1) + 1)
		cornerPenalty += 3;
	if (array[size_x - 1][size_x - 1] != size_x * size_x)
		cornerPenalty += 3;
	return (cornerPenalty);
}

int adjacentTiles(int** array, int size_x)
{
	int adjacentPenalty = 0;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			int tile = array[i][j];
			if (i > 0 && array[i - 1][j] != tile - size_x)
				adjacentPenalty++;
			if (i < size_x - 1 && array[i + 1][j] != tile + size_x)
				adjacentPenalty++;
			if (j > 0 && array[i][j - 1] != tile - 1)
				adjacentPenalty++;
			if (j < size_x - 1 && array[i][j + 1] != tile + 1)
				adjacentPenalty++;
		}
	}
	return (adjacentPenalty);
}

int invertedPairs(int** array, int size_x)
{
	int inversions = 0;
	std::vector<int> tiles;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x; j++)
			tiles.push_back(array[i][j]);
	}
	for (size_t i = 0; i < tiles.size(); i++)
	{
		for (size_t j = i + 1; j < tiles.size(); j++)
		{
			if (tiles[i] != 0 && tiles[j] != 0 && tiles[i] > tiles[j])
				inversions++;
		}
	}
	return (inversions);
}

int linearSequence(int** array, int size_x)
{
	int outOfSequence = 0;
	int tileValue = 1;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			if (array[i][j] != 0)
			{
				if (array[i][j] != tileValue)
					outOfSequence++;
				tileValue = (tileValue + 1) % (size_x * size_x);
			}
		}
	}
	return (outOfSequence);
}

int distantTiles(int** array, int size_x)
{
	int value = 0;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			int tile = array[i][j];
			if (tile == 0)
				continue;
			int target_i = (tile - 1) / size_x;
			int target_j = (tile - 1) % size_x;
			value += std::pow(std::abs(i - target_i), 2) + std::pow(std::abs(j - target_j), 2);
		}
	}
	return (value);
}

int edgeTiles(int** array, int size_x)
{
	int value = 0;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			int tile = array[i][j];
			if (tile == 0)
				continue;
			int target_i = (tile - 1) / size_x;
			int target_j = (tile - 1) % size_x;
			bool isTargetEdge = (target_i == 0 || target_i == size_x - 1 || target_j == 0 || target_j == size_x - 1);
			bool isCurrentEdge = (i == 0 || i == size_x - 1 || j == 0 || j == size_x - 1);
			if (isTargetEdge && !isCurrentEdge)
				value += 4;
			else if (!isTargetEdge && isCurrentEdge)
				value += 2;
		}
	}
	return (value);
}

int isolatedTiles(int** array, int size_x)
{
	int penalty = 0;
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			int tile = array[i][j];
			if (tile == 0)
				continue;
			if (tile + 1 <= size_x * size_x)
			{
				int neighbor_i = (tile) / size_x;
				int neighbor_j = (tile) % size_x;
				int distance = std::abs(i - neighbor_i) + std::abs(j - neighbor_j);
				if (distance > 1)
					penalty += distance;
			}
			if (tile - 1 > 0)
			{
				int neighbor_i = (tile - 2) / size_x;
				int neighbor_j = (tile - 2) % size_x;
				int distance = std::abs(i - neighbor_i) + std::abs(j - neighbor_j);
				if (distance > 1)
					penalty += distance;
			}
		}
	}
	return (penalty);
}

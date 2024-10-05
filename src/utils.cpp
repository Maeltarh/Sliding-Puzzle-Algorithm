/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:06:11 by mhugueno          #+#    #+#             */
/*   Updated: 2024/04/19 16:46:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"

int	isInArray(int **array, int x, int sizeL, int value)
{
	for (int i = 0; i <= x; i++)
	{
		for (int y = 0; y < sizeL; y++)
		{
			if (array[i][y] == value)
				return (1);
		}
	}
	return (0);
}

bool	isSolvable(int** array, int x)
{
	int	value = 0;
	std::vector<int> board;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (array[i][j] != 0)
				board.push_back(array[i][j]);
		}
	}
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = i; j < board.size(); j--)
		{
			if (board[j] > board[i])
				value++;
		}
	}
	if ((x % 2) != 0 && (value % 2) == 0)
		return (true);
	else if ((x % 2) == 0)
	{
		int	ligne = 1;
		for (int i = (x - 1); i >= 0; i--)
		{
			bool toggle = false;
			for (int j = 0; j < x; j++)
			{
				if (array[i][j] == 0)
					toggle = true;
			}
			if (toggle == true)
				break;
			ligne++;
		}
		if ((ligne % 2) == 0 && (value % 2) != 0)
			return (true);
		else if ((ligne % 2) != 0 && (value % 2) == 0)
			return (true);
	}
	return (false);
}

void	congratulation(int timeComplexity, int sizeComplexity, int moveN)
{
	std::cout << "Final state found !" << std::endl;
	std::cout << "Here are some data about the process :" << std::endl;
	std::cout << "- Number of move to win : " << moveN << std::endl;
	std::cout << "- Complexity in time : " << timeComplexity << std::endl;
	std::cout << "- Complexity in size : " << sizeComplexity << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:33:09 by mhugueno          #+#    #+#             */
/*   Updated: 2024/05/04 17:25:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"
#include "node.hpp"

int main(int arg, char *argv[])
{
	if (arg != 4 && arg != 5)
	{
		std::cerr << "Wrong number of arguments." << std::endl;
		return (1);
	}
	std::string verif = argv[2];
	std::string mode = argv[3];
	std::string heuristic = "none";
	if (arg == 5)
	{
		heuristic = argv[4];
		if (heuristic != "manhattanDistance" && heuristic != "rowColCheck" && heuristic != "linearConflict" && heuristic != "cornerTiles" && heuristic != "adjacentTiles" && heuristic != "invertedPairs" && heuristic != "distantTiles" && heuristic != "edgeTiles" && heuristic != "isolatedTiles")
		{
			std::cerr << "Wrong name of heuristic." << std::endl;
			return (1);
		}
	}
	node* game = new node(mode, heuristic);
	if (verif == "random" || verif == "parse")
	{
		if (verif == "random")
		{
			game->setUp(atoi(argv[1]));
			game->randomise();
			while (!isSolvable(game->getArray(), game->getX()))
			{
				game->deleteArray();
				game->setUp(atoi(argv[1]));
				game->randomise();
			}
		}
		else
		{
			std::ifstream file(argv[1]);
			if (!file.is_open())
			{
				std::cerr << "Failed to open the file." << std::endl;
				return (1);
			}
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			game->parse(content);
			if (!isSolvable(game->getArray(), game->getX()))
			{
				std::cerr << "This puzzle is unsolvable !" << std::endl;
				delete (game);
				exit (0);
			}
		}
		game->calcTargetNode();
		game->calcStartNode();

		auto start = std::chrono::high_resolution_clock::now();
		aStar(*game);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << "We found the solution in : " << duration.count() << " secondes." << std::endl;
	}
	else
	{
		std::cerr << "Wrong arguments." << std::endl;
		delete (game);
		return (1);
	}
	delete (game);
	return (0);
}

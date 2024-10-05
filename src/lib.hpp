/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:49:19 by mhugueno          #+#    #+#             */
/*   Updated: 2024/04/25 14:29:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <map>
#include <functional>

class node;

int		isInArray(int	**array, int x, int sizeL, int value);
bool	isSolvable(int** array, int x);
void	congratulation(int timeComplexity, int sizeComplexity, int moveN);

void	aStar(node& game);

int		manhattanDistance(int** array, int size_x);
int		rowColCheck(int** array, int size_x);
int		cornerTiles(int** array, int size_x);
int		linearConflict(int** array, int size_x);
int		adjacentTiles(int** array, int size_x);
int		invertedPairs(int** array, int size_x);
int		linearSequence(int** array, int size_x);
int		distantTiles(int** array, int size_x);
int		edgeTiles(int** array, int size_x);
int		isolatedTiles(int** array, int size_x);

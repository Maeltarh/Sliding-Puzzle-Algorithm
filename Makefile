# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 02:30:33 by mhugueno          #+#    #+#              #
#    Updated: 2024/04/19 17:14:59 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME		= n-puzzle

CC			= c++
FLAGS		= -Wall -Wextra -Werror -std=c++11
RM			= rm -rf

SRC_DIR = src

OBJDIR = obj

FILES		= main node algo utils heuristic

SRC			= $(addprefix $(SRC_DIR)/, $(FILES:=.cpp))
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= $(SRC_DIR)/node.hpp

RED = \033[38;5;196m
ORANGE = \033[38;5;208m
YELLOW = \033[38;5;226m
LIGHT_GREEN = \033[38;5;154m
GREEN = \033[38;5;46m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(OBJ) $(OPTS) -o $(NAME)
	@echo ""
	@python3 skin.py "$(NAME)"
	@echo ""
	@echo -e "$(NC)Welcome to n-puzzle ! Here's how to use it :"
	@echo "  You can start with three arguments, one to use a defined set of tiles, or one to creat a random set :"
	@echo "   - ./n-puzzle <puzzle/file_name> parse"
	@echo "   - ./n-puzzle <number of tiles per side> random"
	@echo "   - Next you can chose the search settings : default / uniform / greedy"
	@echo "   - Finally, you can choose to use only one heuristic, but I must warn you, this is not recommended :"
	@echo "           manhattanDistance"
	@echo "           rowColCheck"
	@echo "           linearConflict"
	@echo "           cornerTiles"
	@echo "           adjacentTiles"
	@echo "           invertedPairs"
	@echo "           distantTiles"
	@echo "           edgeTiles"
	@echo "           isolatedTiles"

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@echo -n -e "$(NC)  [$(RED)■■ / 5%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(RED)■■■ / 10%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(RED)■■■■ / 15%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(RED)■■■■■■ / 20%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■ / 25%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■■■ / 30%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■■■■ / 35%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■■■■■■ / 40%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■ / 45%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■■■ / 50%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■■■■ / 55%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■■■■■■ / 60%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■ / 65%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■■■ / 70%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■■■■ / 75%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■■■■■■ / 80%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■ / 85%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■■■ / 90%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■■■■ / 95%$(NC)] - $<\r"
	@sleep 0.05
	@echo -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ / 100%$(NC)] - $<\r"
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

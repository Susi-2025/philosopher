# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 12:30:39 by vinguyen          #+#    #+#              #
#    Updated: 2025/09/07 17:56:59 by vinguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude
#LDLIBS = -lreadline

SRC_DIRS = src
OBJ_DIR = object

#LIBFT_DIR = ./libft
#LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC =	$(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
		
OBJ =$(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)
#all:$(LIBFT_LIB) $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.SECONDARY: $(OBJ) $(LIBFT_OBJ)

#Build library
#$(LIBFT_LIB):
#	@$(MAKE) -C $(LIBFT_DIR)

#Build final executable
#$(NAME): $(OBJ) $(LIBFT_LIB)
#	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDLIBS) $(LIBFT_LIB)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDLIBS)

#cleaning
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

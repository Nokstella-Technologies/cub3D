# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 16:11:34 by prafael-          #+#    #+#              #
#    Updated: 2022/11/28 17:53:22 by llima-ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g3 -I ./src -I./libft -I./minilibx 

CC = gcc

LIBFT = ./libft/libft.a

MINILIBX = ./minilibx/libmlx_Linux.a

SRC =	main.c read_map.c error.c read_map_utils.c

OBJ = $(SRC:.c=.o)

DIROBJ = ./obj/

all: $(NAME)

$(NAME): $(addprefix $(DIROBJ), $(OBJ)) $(LIBFT) $(MINILIBX)
	$(CC) $(addprefix $(DIROBJ),$(OBJ)) $(CFLAGS) -o $(NAME) -L./libft -L./minilibx-L./libft -L./minilibx -lft -lmlx_Linux -lXext -lX11 -lm -lz

$(DIROBJ):
	mkdir -p $(DIROBJ)

$(addprefix $(DIROBJ), $(OBJ)): $(DIROBJ)
	gcc $(CFLAGS) -c $(addprefix ./src/, $(SRC)) -lft -lmlx_Linux
	mv $(OBJ) ./obj/

$(LIBFT):
	make others -C ./libft

$(MINILIBX):
	./minilibx/configure

clean:
	rm -rf $(DIROBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./cub3d map.cub

run:
	make test -C ./test

.PHONY: all clean test valgrind fclean re
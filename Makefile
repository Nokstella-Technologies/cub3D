# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 16:11:34 by prafael-          #+#    #+#              #
#    Updated: 2022/11/12 12:48:54 by llima-ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g3

CC = gcc

LIBFT = ./libft/libft.a

MINILIBX = ./minilibx/libmlx_Linux.a

SRC =	main.c read_map.c error.c read_map_utils.c

OBJ = $(SRC:.c=.o)

DIROBJ = ./obj/

all: $(NAME)

$(NAME): $(addprefix $(DIROBJ), $(OBJ)) $(LIBFT) $(MINILIBX)
	$(CC) $(addprefix $(DIROBJ),$(OBJ)) $(CFLAGS) v-o  $(NAME)

$(DIROBJ):
	mkdir -p $(DIROBJ)

$(addprefix $(DIROBJ), $(OBJ)): $(DIROBJ)
	gcc $(CFLAGS) -I . -c $(addprefix ./src/, $(SRC))
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

unitest: $(LIBFT) $(MINILIBX)
	g++  -g3 -I . ./src/read_map_utils.c ./src/error.c ./test/*.cpp  -Lmlx_Linux -lmlx_Linux -L ./minilibx -Imlx_Linux -L ./libft -lft -lXext -lX11 -lm -lz 
	./a.out

.PHONY: all clean teste valgrind fclean re
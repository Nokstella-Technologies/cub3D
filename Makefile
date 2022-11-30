# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 16:11:34 by prafael-          #+#    #+#              #
#    Updated: 2022/11/30 02:02:14 by llima-ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g3 -I ./src -I./libft -I./minilibx 

CC = gcc

LIBFT = ./libft/libft.a

MINILIBX = ./minilibx/libmlx_Linux.a

SRC =	main.c read_map.c error.c read_map_utils.c validation_map.c \
		print_minimap.c start_game.c math_utils.c draw_formats.c

OBJ = $(SRC:.c=.o)

DIROBJ = ./obj/

SANITIZE = -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

all: $(NAME)

$(NAME): $(addprefix $(DIROBJ), $(OBJ)) $(LIBFT) $(MINILIBX)
	$(CC)  -L./libft -L./minilibx  $(addprefix $(DIROBJ),$(OBJ)) $(CFLAGS) -lft -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME) $(SANITIZE) 

$(DIROBJ):
	mkdir -p $(DIROBJ)

$(addprefix $(DIROBJ), $(OBJ)): $(DIROBJ)
	$(CC) -L./libft -L./minilibx  $(CFLAGS) -c $(addprefix ./src/, $(SRC)) -lft -lmlx_Linux
	mv $(OBJ) ./obj/

$(LIBFT):
	make others -C ./libft

$(MINILIBX):
	./minilibx/configure

clean:
	rm -rf $(DIROBJ)
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./cub3d map.cub

run:
	make test -C ./test

#-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
.PHONY: all clean test valgrind fclean re
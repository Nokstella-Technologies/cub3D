# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 16:11:34 by prafael-          #+#    #+#              #
#    Updated: 2022/12/13 15:59:09 by llima-ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g3 

CC = gcc

LIBS = -L./lib/libft  -L./lib/minilibx -I./src -I./lib/libft -I./lib/minilibx

LIBFT = ./lib/libft/libft.a
MINILIBX = ./lib/minilibx/libmlx_Linux.a

SRC =	main.c read_map.c error.c read_map_utils.c validation_map.c \
		print_map.c start_game.c math_utils.c draw_formats.c \
		print_minimap_bonus.c

OBJ = $(SRC:.c=.o)

T_OBJ = $(addprefix $(DIROBJ), $(OBJ)) $(LIBFT)
DIROBJ = ./obj/

SANITIZE = -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment 

all: $(NAME)

$(NAME): $(T_OBJ) $(MINILIBX)
	$(CC)  $(LIBS) $(addprefix $(DIROBJ),$(OBJ)) $(CFLAGS) -lft -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME) $(SANITIZE)

$(DIROBJ):
	mkdir -p $(DIROBJ)

$(T_OBJ): $(DIROBJ)
	$(CC) $(LIBS) $(CFLAGS) -c $(addprefix ./src/, $(SRC)) -lft -lmlx_Linux -lXext -lX11 -lm -lz && mv $(OBJ) ./obj/

$(LIBFT):
	make others -C ./lib/libft

$(MINILIBX):
	cd ./lib/minilibx && ./configure

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
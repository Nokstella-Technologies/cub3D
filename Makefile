# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 16:11:34 by prafael-          #+#    #+#              #
#    Updated: 2023/01/12 18:11:46 by llima-ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g3

CC = gcc

HEADER = -L./lib/libft  -L./lib/minilibx -I./src -I./lib/libft -I./lib/minilibx

LIBFT		= ./lib/libft/libft.a
MINILIBX	= ./lib/minilibx/libmlx_Linux.a
SRC			= main.c read_map.c error.c read_map_utils.c validation_map.c \
		print_map.c start_game.c math_utils.c draw_formats.c \
		print_minimap_bonus.c calc_ray.c player_moves.c get_color.c \
		init_sprites.c

LIBS		= -lft -lmlx_Linux -lXext -lX11 -lm -lz

SANITIZE	= -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment 

OBJDIR		= objs
SRCDIR		= src
SRCS		= $(addprefix $(SRCDIR)/, $(SRC))
OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(OBJS)  $(CFLAGS) $(HEADER) $(LIBS) -o $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $(HEADER) $< -o $@ $(LIBS)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBFT):
	make others -C ./lib/libft

$(MINILIBX):
	cd ./lib/minilibx && ./configure

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
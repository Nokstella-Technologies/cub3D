# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coder <coder@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 16:48:25 by llima-ce          #+#    #+#              #
#    Updated: 2023/02/18 01:36:06 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

CFLAGS = -Wall -Wextra -Werror -g3

CC = gcc

HEADER = -L./lib/libft  -L./lib/minilibx -I./src -I./lib/libft -I./lib/minilibx

LIBFT		= ./lib/libft/libft.a
MINILIBX	= ./lib/minilibx/libmlx_Linux.a
SRC			= main.c read_map.c error.c read_map_utils.c validation_map.c \
		print_map.c start_game.c math_utils.c draw_formats.c \
		print_minimap.c calc_ray.c player_moves.c get_color.c \
		init_sprites.c
BONUS_SRC	= main_bonus.c read_map_bonus.c error_bonus.c \
		read_map_utils_bonus.c validation_map_bonus.c \
		print_map_bonus.c start_game_bonus.c math_utils_bonus.c \
		draw_formats_bonus.c print_minimap_bonus.c calc_ray_bonus.c \
		player_moves_bonus.c get_color_bonus.c init_sprites_bonus.c


LIBS		= -lft -lmlx_Linux -lXext -lX11 -lm -lz

MINILIBX_DIR = ./lib/minilibx

SANITIZE	= -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment 

OBJDIR		= objs
SRCDIR		= src
BONUSDIR	= src_bonus
BONUS_SRCS	= $(addprefix $(BONUSDIR)/, $(BONUS_SRC))
SRCS		= $(addprefix $(SRCDIR)/, $(SRC))
OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_BONUS	= $(BONUS_SRCS:$(BONUSDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(OBJS)  $(CFLAGS) $(HEADER) $(LIBS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS):  $(OBJDIR) $(OBJS_BONUS) $(LIBFT) $(MINILIBX)
	$(CC) $(OBJS_BONUS)  $(CFLAGS) $(HEADER) $(LIBS) -o $(NAME_BONUS)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $(HEADER) $< -o $@ $(LIBS)


$(OBJDIR)/%.o: $(BONUSDIR)/%.c
	$(CC) -c $(CFLAGS) $(HEADER) $< -o $@ $(LIBS)


$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBFT):
	make others -C ./lib/libft

$(MINILIBX): $(MINILIBX_DIR)
	cd ./lib/minilibx && ./configure
	
$(MINILIBX_DIR):
	git clone https://github.com/42Paris/minilibx-linux.git ./lib/minilibx

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OBJ)
	make fclean -C ./lib/libft

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	rm -rf $(MINILIBX_DIR)

re: fclean all

.PHONY: all clean fclean re
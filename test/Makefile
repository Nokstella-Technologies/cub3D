NAME = test

UNITSFLAGS = -g3 -std=c++17 -Wall -Wextra -pthread -I/home/luiz/42/googletest/build -L/home/luiz/42/googletest/build 

LIBFT_FLAGS = -I../src -I../libft -I../minilibx -L../minilibx

LIBFT_SRC = ../libft/**/*.c ../libft/**/**/*.c

C_SRC = ../src/read_map_utils.c ../src/read_map.c ../src/error.c

TEST_SRC = ./main.cpp ./read_map_utils.cpp

all: $(NAME)

$(NAME): $(MINILIBX)
	g++ $(UNITSFLAGS) $(LIBFT_FLAGS) $(UNITSRC) $(LIBFT_SRC) $(C_SRC) $(TEST_SRC) -lmlx_Linux -lXext -lX11 -lm -lz -lgtest -o $(NAME)

$(MINILIBX):
	./minilibx/configure

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean test fclean re
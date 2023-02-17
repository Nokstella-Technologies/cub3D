/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:29 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 11:30:21 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void test_read(t_game *game)
// {
// 	int i;

// 	i = -1;
// 	ft_printf("no: %s\nso: %s\nwe: %s\nea: %s\ncolor floor: rgb(%i,%i,%i)
// \ncolor celling: rgb(%i,%i,%i)\n", game->cmap->no, game->cmap->so, 
// game->cmap->we, game->cmap->ea, game->cmap->floor_c[0], game->cmap->floor_c
// [1], 
// game->cmap->floor_c[2] ,game->cmap->celling_c[0], game->cmap->celling_c[1], 
// game->cmap->celling_c[2]);
// 	while (++i < game->cmap->map_y) {
// 		printf("%s\n", game->cmap->map[i]);
// 	}
// }

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (argc == 2)
	{
		game = read_map(argv);
		start_game(game);
		close_all(game);
	}
}

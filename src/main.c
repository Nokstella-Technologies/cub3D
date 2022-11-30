/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:29 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/30 14:48:26 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


// float	px,py,pdx,pdy,pa;

// int	key_hook(int keycode, t_vars *vars)
// {
// 	if (keycode == KEY_D || keycode == KEY_RIGHT){
// 		pa+= 0.1;
// 		if(pa > 2*PI)
// 			pa -= 2*PI;
// 		pdx = cos(pa) * 5;
// 		pdy = sin(pa) * 5;
// 	}
// 	else if (keycode == KEY_A || keycode == KEY_LEFT){
// 		pa-= 0.1; 
// 		if(pa < 0)
// 			pa += 2*PI;
// 		pdx = cos(pa) * 5;
// 		pdy = sin(pa) * 5;
// 	}
// 	else if (keycode == KEY_S || keycode == KEY_DOWN){ px-= pdx; py-= pdy; }
// 	else if (keycode == KEY_W || keycode == KEY_UP){ px+= pdx; py+= pdy; }
// }

// void print_sprint(t_vars *vars, int x, int y, void *img)
// {
// 	mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
// }


void test_read(t_game *game)
{
	int i;

	i = -1;
	ft_printf("no: %s\nso: %s\nwe: %s\nea: %s\ncolor floor: rgb(%i,%i,%i)\ncolor celling: rgb(%i,%i,%i)\n", game->cmap->no, game->cmap->so, game->cmap->we, game->cmap->ea, game->cmap->floor_c[0], game->cmap->floor_c[1], game->cmap->floor_c[2] ,game->cmap->celling_c[0], game->cmap->celling_c[1], game->cmap->celling_c[2]);
	while (++i < game->cmap->map_y) {
		printf("%s\n", game->cmap->map[i]);
	}
}

int	main(int argc,char **argv)
{
	t_game	*game;
	// t_vars	vars;
	// t_data	img;
	game = NULL;
	if(argc == 2) {
		game = read_map(argv);
		test_read(game);
		start_game(game);
		(void)argv;
		(void)game;
		
	}
}

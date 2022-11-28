/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:29 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/28 18:09:43 by llima-ce         ###   ########.fr       */
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

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// void	square(t_data *img, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < 32)
// 	{
// 		j = -1;
// 		while (++j < 32)
// 			my_mlx_pixel_put(img, x + i, y + j, color);
// 	}
// }

// void	square_player(t_data *img, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < 5)
// 	{
// 		j = -1;
// 		while (++j < 5)
// 		{
// 			if (i == 0 || i == 4)
// 				my_mlx_pixel_put(img, x + i, y + j, color);
// 			else if (j == 0 || j == 4) 
// 				my_mlx_pixel_put(img, x + i, y + j, color);
// 		}
// 	}
// }

// void	mini_map(t_data *img)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;

// 	i = -1;
// 	y = 5;
// 	while (++i < 5)
// 	{
// 		j = -1;
// 		x = 5;
// 		while (++j < 5)
// 		{
// 			if (map[i][j] == '1')
// 				square(img, x, y, 0x00FFFFFF);
// 			else if (map[i][j] == 'N')
// 				square_player(img, x, y, 0x0021F505);
// 			x += 34;
// 		}
// 		y += 34;
// 	}
// }

void test_read(t_game *game)
{
	int i;

	i = -1;
	ft_printf("no: %s\nso: %s\nwe: %s\nea: %s\ncolor floor: rgb(%i,%i,%i)\ncolor celling: rgb(%i,%i,%i)\n", game->cmap->no, game->cmap->so, game->cmap->we, game->cmap->ea, game->cmap->floor_c[0], game->cmap->floor_c[1], game->cmap->floor_c[2] ,game->cmap->celing_c[0], game->cmap->celing_c[1], game->cmap->celing_c[2]);
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
		(void)argv;
		(void)game;
		// vars.mlx = mlx_init();
		// vars.win = mlx_new_window(vars.mlx, 800, 600, "Hello world!");
		// // img1 = mlx_xpm_file_to_image(vars.mlx, relative_path, &x, &x);
		// img.img = mlx_new_image(vars.mlx, 600, 600);
		// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		// 	&img.line_length, &img.endian);
		// mini_map(&img);
		// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
		// mlx_key_hook(vars.win, key_hook, &vars);
		// mlx_loop(vars.mlx);
	}
}

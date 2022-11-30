/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:05:55 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/29 16:13:30 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

int	draw_line(t_game *game, int begin[2], int end[2], int color)
{
	double	delta[2];
	int		pixels;
	double	pixel[2];

	delta[0] = end[0] - begin[0]; 
	delta[1] = end[1] - begin[1];
	pixels = sqrt((delta[0] * delta[0]) + (delta[1] * delta[1]));
	delta[0] /= pixels;
	delta[1] /= pixels;
	pixel[0] = begin[0];
	pixel[1] = begin[1];
	while (pixels)
	{
		mlx_pixel_put(game->mlx, game->win, pixel[0], pixel[1], color);
		pixel[0] += delta[0];
		pixel[1] += delta[1];
		--pixels;
	}
	return (0);
}

int	key_hook(int key, t_game *game)
{
	if (key == 113 || key == KEY_ESC)
		clean_all(game);
	print_mini_map(game);

	return (0);
}

void	start_game(t_game *game)
{

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 800, 900, "Hello world!");
	// draw_line(game, (int [2]){0, 0}, (int [2]) {800, 1200}, 0xFFFFFF);
	// img1 = mlx_xpm_file_to_image(vars.mlx, relative_path, &x, &x);
	print_mini_map(game);
	// img.img = mlx_new_image(vars.mlx, 800, 600);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 	&img.line_length, &img.endian);
	// mini_map(&img);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(game->win, &key_hook, game);
	mlx_loop(game->mlx);
}
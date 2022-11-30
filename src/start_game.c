/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:05:55 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/30 02:01:20 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

void	move(t_game *game, int keycode)
{
	if (keycode == KEY_A || keycode == KEY_LEFT || keycode == KEY_D
		|| keycode == KEY_RIGHT)
	{
		if (keycode == KEY_D || keycode == KEY_RIGHT)
			game->hero->pa -= 5;
		else
			game->hero->pa += 5;
		game->hero->pa = fix_ang(game->hero->pa);
		game->hero->pdx = cos(DEGTORAD(game->hero->pa));
		game->hero->pdy = -sin(DEGTORAD(game->hero->pa));
	}
	else if (keycode == KEY_W || keycode == KEY_UP)
	{
		game->cmap->hero->px += game->cmap->hero->pdx * 5;
		game->cmap->hero->py += game->cmap->hero->pdy * 5;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		game->cmap->hero->px-= game->cmap->hero->pdx * 5;
		game->cmap->hero->py-= game->cmap->hero->pdy * 5;
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 113 || keycode == KEY_ESC)
		clean_all(game);
	else if (keycode == KEY_D || keycode == KEY_RIGHT || keycode == KEY_A
		|| keycode == KEY_LEFT)
		move(game, keycode);
	else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_W
		|| keycode == KEY_UP)
		move(game, keycode);
	print_mini_map(game);
	return (0);
}

void	start_game(t_game *game)
{

	game->hero =  game->cmap->hero;
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
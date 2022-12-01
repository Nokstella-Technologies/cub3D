/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:05:55 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/30 23:54:26 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

void	move(t_game *game, int keycode)
{
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_RIGHT)
			game->hero->pa -= 0.2*30;
		else if (keycode == KEY_LEFT)
			game->hero->pa += 0.2*30;
		game->hero->pa = fix_ang(game->hero->pa);
		game->hero->pdx = cos(deg_to_rad(game->hero->pa));
		game->hero->pdy = -sin(deg_to_rad(game->hero->pa));
	}
}

void	move_forward(t_game *game, int keycode)
{
	int	mx;
	int	my;

	mx = game->cmap->hero->pdx * 0.2*30;
	my = game->cmap->hero->pdy * 0.2*30;
	if ((keycode == KEY_W) && game->cmap->map[(int)(game->cmap->hero->py + my + 30) / 64][(int)(game->cmap->hero->px + mx + 30) / 64] != '1')
	{
		game->cmap->hero->px += mx;
		game->cmap->hero->py += my;
	}
	else if ((keycode == KEY_S) && game->cmap->map[(int)(game->cmap->hero->py - my - 30) / 64][(int)(game->cmap->hero->px - mx - 30) / 64] != '1')
	{
		game->cmap->hero->px-= mx;
		game->cmap->hero->py-= my;
	}
	else if ((keycode == KEY_D) && game->cmap->map[(int)(game->cmap->hero->py + mx + 30) / 64][(int)(game->cmap->hero->px + my + 30) / 64] != '1')
	{
		game->cmap->hero->py+= mx;
		game->cmap->hero->px+= my;
	}
	else if ((keycode == KEY_A) && game->cmap->map[(int)(game->cmap->hero->py - mx - 30) / 64][(int)(game->cmap->hero->px - my - 30) / 64] != '1')
	{
		game->cmap->hero->px-= my;
		game->cmap->hero->py-= mx;
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 113 || keycode == KEY_ESC)
		clean_all(game);
	else if ( keycode == KEY_RIGHT || keycode == KEY_LEFT)
		move(game, keycode);
	else if (keycode == KEY_D || keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_DOWN || keycode == KEY_W || keycode == KEY_UP)
		move_forward(game, keycode);
	return (0);
}

static void	*img_init(char *img, void *mlx)
{
	void	*img_ptr;
	int		width;

	(void ) img;
	img_ptr = mlx_xpm_file_to_image(mlx, "./assets/bluebrick.xpm", &width, &width);
	return (img_ptr);
}

void	init_sprites(t_game *game)
{
	t_sprite *sprite;

	sprite = malloc(sizeof(t_sprite));
	game->sprite = sprite;
	game->sprite->ea = img_init(game->cmap->ea, game->mlx);
	game->sprite->no = img_init(game->cmap->no, game->mlx);
	game->sprite->so = img_init(game->cmap->so, game->mlx);
	game->sprite->we = img_init(game->cmap->we, game->mlx);
	if (!game->sprite->ea || !game->sprite->no || !game->sprite->so
		|| !game->sprite->we)
		game->err = custom_error("failed to load sprites", 520);
}

void	start_game(t_game *game)
{
	t_data	img;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, MAP_X, MAP_Y, "Cub42D");
	if(!game->mlx || !game->win)
	{
		game->err = custom_error("failed to open the screen", 520);
		clean_all(game);
	}
	init_sprites(game);
	img.img = mlx_new_image(game->mlx, MAP_X, MAP_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	game->img = &img;
	game->hero = game->cmap->hero;
	if (game->err != 0)
		clean_all(game);
	mlx_key_hook(game->win, &key_hook, game);
	mlx_hook(game->win, 17, 0, &close_all, game);
	mlx_hook(game->win, 9, 1L << 21, &print_mini_map, game);
	mlx_loop_hook(game->mlx, &print_mini_map, game);
	mlx_loop(game->mlx);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:05:55 by llima-ce          #+#    #+#             */
/*   Updated: 2022/12/01 19:47:42 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

int	Key_pressed(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->move->w = TRUE;
	if (keycode == KEY_S)
		game->move->s = TRUE;
	if (keycode == KEY_LEFT)
		game->move->rot_l = TRUE;
	if (keycode == KEY_RIGHT)
		game->move->rot_r = TRUE;
	if (keycode == KEY_A)
		game->move->a = TRUE;
	if (keycode == KEY_D)
		game->move->d = TRUE;
	return (0);
}

void img_init(char *name, void *mlx, t_img *img)
{
	int		width;

	(void)name;
	img->img_ptr = mlx_xpm_file_to_image(mlx, "./assets/bluebrick.xpm", &width,
		&width);
	img->dump = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_all(game);
	if (keycode == KEY_W)
		game->move->w = FALSE;
	if (keycode == KEY_S)
		game->move->s = FALSE;
	if (keycode == KEY_LEFT)
		game->move->rot_l = FALSE;
	if (keycode == KEY_RIGHT)
		game->move->rot_r = FALSE;
	if (keycode == KEY_A)
		game->move->a = FALSE;
	if (keycode == KEY_D)
		game->move->d = FALSE;
	return (0);
}

void	init_sprites(t_game *game)
{
	t_sprite *sprite;
	t_move *move;

	sprite = malloc(sizeof(t_sprite));
	move = malloc(sizeof(t_move));
	game->sprite = sprite;
	game->move = move;
	move->a = FALSE;
	move->s = FALSE;
	move->d = FALSE;
	move->w = FALSE;
	move->rot_l = FALSE;
	move->rot_r = FALSE;
	game->sprite->ea = malloc(sizeof(t_img));
	game->sprite->no = malloc(sizeof(t_img));
	game->sprite->so = malloc(sizeof(t_img));
	game->sprite->we = malloc(sizeof(t_img));
	img_init(game->cmap->ea, game->mlx, game->sprite->ea);
	img_init(game->cmap->no, game->mlx, game->sprite->no);
	img_init(game->cmap->so, game->mlx, game->sprite->so);
	img_init(game->cmap->we, game->mlx, game->sprite->we);
	if (!game->sprite->ea || !game->sprite->no || !game->sprite->so
		|| !game->sprite->we)
		game->err = custom_error("failed to load sprites", 520);
}


void loop(t_game *game)
{
	mlx_do_sync(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, &Key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, &key_release, game);
	mlx_hook(game->win, 17, 0, &close_all, game);
	// mlx_hook(game->win, 9, 1L << 21, &print_mini_map, game);
	mlx_loop_hook(game->mlx, &print_mini_map, game);
	mlx_loop(game->mlx);
}

void	start_game(t_game *game)
{
	t_img	img;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, MAP_X, MAP_Y, "Cub42D");
	if(!game->mlx || !game->win)
	{
		game->err = custom_error("failed to open the screen", 520);
		clean_all(game);
	}
	init_sprites(game);
	img.img_ptr = mlx_new_image(game->mlx, MAP_X, MAP_Y);
	img.dump = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	game->img = &img;
	game->hero = game->cmap->hero;
	if (game->err != 0)
		clean_all(game);
	loop(game);
}
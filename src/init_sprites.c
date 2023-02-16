/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:54:40 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/16 23:47:32 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	img_init(char *name, void *mlx, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx, name, &img->width,
			&img->height);
	if (img->img_ptr == NULL || img->width != 64 || img->height != 64)
		return (custom_error("failed to load sprites", 520));
	img->dump = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l,
			&img->endian);
	return (0);
}

void	init_sprites(t_game *game)
{
	t_sprite	*sprite;
	t_move		*move;

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
	game->err = img_init(game->cmap->ea, game->mlx, game->sprite->ea);
	game->err = img_init(game->cmap->no, game->mlx, game->sprite->no);
	game->err = img_init(game->cmap->so, game->mlx, game->sprite->so);
	game->err = img_init(game->cmap->we, game->mlx, game->sprite->we);
}

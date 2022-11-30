/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:51:21 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/29 15:54:55 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	square_full(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
			mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
	}
}

void	square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			if (i == 0 || i == 16)
				mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
			else if (j == 0 || j == 16) 
				mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
		}
	}
}

void	print_mini_map(t_game *game)
{
	int	a;
	int	b;
	int	xy[2];

	a = game->cmap->hero->y - 7;
	if (a < 0)
		a = 0;
	xy[1] = 620;
	while(a < game->cmap->hero->y + 7 && a < game->cmap->map_y)
	{
		xy[0] = 20;
		b = game->cmap->hero->x - 7;
		if (b < 0)
			b = 0;
		while(b < game->cmap->hero->x + 7 && b < (int)LEN(game->cmap->map[a]))
		{
			if (game->cmap->map[a][b] == '1')
				square_full(game, xy[0], xy[1], 0x006437);
			else if (game->cmap->map[a][b] == '0')
				square(game, xy[0], xy[1], 0xFFFFFF);
			else if (game->cmap->map[a][b] != ' ')
				square_full(game, xy[0], xy[1], 0xE7C602);
			
			xy[0] += 19;
			b++;
		}
		xy[1] += 19;
		a++;
	}
}
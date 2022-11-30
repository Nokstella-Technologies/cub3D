/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_formats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 02:01:40 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/30 02:02:40 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	square_full(t_game *game, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < 20)
// 	{
// 		j = -1;
// 		while (++j < 20)
// 			mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
// 	}
// }

void	square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 20)
	{
		j = -1;
		while (++j < 20)
		{
			if (i == 0 || i == 20)
				mlx_pixel_put(game->mlx, game->win, x + i, y + j, 0x000000);
			else if (j == 0 || j == 20) 
				mlx_pixel_put(game->mlx, game->win, x + i, y + j, 0x000000);
			else
				mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
		}
	}
}

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
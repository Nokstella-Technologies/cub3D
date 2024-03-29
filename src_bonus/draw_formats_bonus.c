/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_formats_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 02:01:40 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/18 21:22:01 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->dump + (y * data->size_l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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
				my_mlx_pixel_put(game->img, x + i, y + j, 0x000000);
			else if (j == 0 || j == 20)
				my_mlx_pixel_put(game->img, x + i, y + j, 0x000000);
			else
				my_mlx_pixel_put(game->img, x + i, y + j, color);
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
		my_mlx_pixel_put(game->img, pixel[0], pixel[1], color);
		pixel[0] += delta[0];
		pixel[1] += delta[1];
		--pixels;
	}
	return (0);
}

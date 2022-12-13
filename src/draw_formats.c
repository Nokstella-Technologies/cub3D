/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_formats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 02:01:40 by llima-ce          #+#    #+#             */
/*   Updated: 2022/12/13 16:02:16 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->dump + (y * data->size_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
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

int	get_color_t(int trgb, char type)
{
	if(type == 'T')
		return ((trgb >> 24) & 0xFF);
	if(type == 'R')
		return ((trgb >> 16) & 0xFF);
	if(type == 'G')
		return ((trgb >> 8) & 0xFF);
	if(type == 'B')
		return (trgb & 0xFF);
	else
		return (0xFFFFFF);
}
int	get_sprite_color(int pixel, char *sprite,int shade)
{
	return(create_trgb(shade, get_color_t((int)sprite[pixel + 2], 'R'), get_color_t((int)sprite[pixel + 1], 'G'), get_color_t((int)sprite[pixel], 'B')));
}


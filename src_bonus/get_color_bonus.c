/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:16:32 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/17 19:49:40 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	get_color_t(int trgb, char type)
{
	if (type == 'T')
		return ((trgb >> 24) & 0xFF);
	if (type == 'R')
		return ((trgb >> 16) & 0xFF);
	if (type == 'G')
		return ((trgb >> 8) & 0xFF);
	if (type == 'B')
		return (trgb & 0xFF);
	else
		return (0xFFFFFF);
}

int	get_sprite_color(int pixel, char *sprite, int shade)
{
	return (create_trgb(shade, get_color_t((int)sprite[pixel + 2], 'R'),
			get_color_t((int)sprite[pixel + 1], 'G'),
			get_color_t((int)sprite[pixel], 'B')));
}

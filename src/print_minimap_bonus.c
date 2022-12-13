/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:42:43 by llima-ce          #+#    #+#             */
/*   Updated: 2022/12/13 16:05:07 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_mini_map(t_game *game, int a, int b)
{
	int	x;
	int	y;

	a = game->hero->y - 5;
	y = 10;
	while(a++ < game->hero->y + 4)
	{
		x = 10;
		b = game->hero->x - 5;
		while (a >= 0 && a < game->cmap->map_y && b++ < game->hero->x + 4)
		{
			if(b >= 0 && b < (int)LEN(game->cmap->map[a]))
			{
				if(game->hero->y == a && game->hero->x == b)
					square(game, x, y, 0xFFFF00);
				else if (game->cmap->map[a][b] == '1')
					square(game, x, y, 0x000000);
				else if (game->cmap->map[a][b] == ' ');
				else
					square(game, x, y, 0xFFFFFF);
			}
			x += 22;
		}
		y += 22;
	}
}
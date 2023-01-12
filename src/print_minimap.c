/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:42:43 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 11:39:18 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_mini_map(t_game *game, int a, int b, int y)
{
	int	x;

	a = game->hero->y - 5;
	while (a++ < game->hero->y + 4)
	{
		x = 10;
		b = game->hero->x - 5;
		while (a >= 0 && a < game->cmap->map_y && b++ < game->hero->x + 4)
		{
			if (b >= 0 && b < (int)ft_strlen(game->cmap->map[a]))
			{
				if (game->hero->y == a && game->hero->x == b)
					square(game, x, y, 0xFADA00);
				else if (game->cmap->map[a][b] == '1')
					square(game, x, y, 0x000000);
				else if (game->cmap->map[a][b] == ' ')
					square(game, x, y, 0x000000);
				else
					square(game, x, y, 0xAFAFAF);
			}
			x += 22;
		}
		y += 22;
	}
}

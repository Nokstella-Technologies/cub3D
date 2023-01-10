/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:49:28 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 11:12:56 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


// static int validation_wall(char **map, int a, int i, t_map *cmap)
// {
// 	if ((a == 0 && i == 0 && map[a + 1][i] != '1' && map[a][i + 1] != '1')
// 		|| (a == cmap->map_y - 1 && i == 0 && map[a - 1][i] != '1'
// 		&& map[a][i + 1] != '1') || (a == 0 && i == (int)(LEN(map[a]) - 1)
// 		&& map[a + 1][i] != '1' && map[a][i - 1] != '1')
// 		|| (a == cmap->map_y - 1 && i == (int)(LEN(map[a]) - 1)
// 		&& map[a - 1][i] != '1' && map[a][i - 1] != '1'))
// 		return (INV_MAP);

// 	return (0);
// }

static int	hero_map(char c, int a, int i, t_map *cmap)
{
	if (cmap->hero != NULL)
		return (INV_MAP);
	cmap->hero = (t_hero *)malloc(1 * sizeof(t_hero));
	cmap->hero->x = i;
	cmap->hero->y = a;
	cmap->hero->px = MAP_S * (i);
	cmap->hero->py = MAP_S * (a);
	if (c == 'E')
		cmap->hero->pa = 0;
	else if (c == 'N')
		cmap->hero->pa = 90;
	else if (c == 'W')
		cmap->hero->pa = 180;
	else if (c == 'S')
		cmap->hero->pa = 270;
	cmap->hero->pdx = cos(deg_to_rad(cmap->hero->pa));
	cmap->hero->pdy = -sin(deg_to_rad(cmap->hero->pa));
	return (0);
}

static int	statemets_validation_map(char **map, int a, int i, t_map *cmap)
{
	(void) cmap;
	if (map[a][i] != ' ' && map[a][i] != '0' && map[a][i] != '1'
		&& map[a][i] != 'N' && map[a][i] != 'S' && map[a][i] != 'E'
		&& map[a][i] != 'W')
		return (INV_MAP);
	if ((a == 0 || i == 0 || i == (int)(ft_strlen(map[a]) - 1)
		|| a == cmap->map_y - 1) && map[a][i] != ' ' && map[a][i] != '1')
		return (INV_MAP);
	// if (map[a][i] == '1')
	// 	return (validation_wall(map, a, i, cmap));
	if (map[a][i] == 'N' || map[a][i] == 'S' || map[a][i] == 'E'
		|| map[a][i] == 'W')
		return(hero_map(map[a][i], a, i, cmap));
	return (0);
}

void	validation_map_line(t_map *cmap, t_game *game)
{
	int	a;
	int	i;

	a = -1;
	while (++a < cmap->map_y)
	{
		if (game->err != 0)
			break ;
		i = -1;
		while (++i < (int)ft_strlen(cmap->map[a]))
		{
			game->err = statemets_validation_map(cmap->map, a, i, cmap);
			if (game->err != 0)
				break ;
		}
	}
	if (game->err != 0)
		custom_error(cmap->map[a - 1], game->err);
}

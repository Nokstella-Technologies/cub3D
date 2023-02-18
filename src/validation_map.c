/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:49:28 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/18 04:56:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_fchstr(char to_find, char *options)
{
	int	a;

	a = -1;
	while (++a < (int)ft_strlen(options))
	{
		if (to_find == options[a])
			return (a + 1);
	}
	return (0);
}

static int	verify_if_is_inside_walls(char **map, int y, int x, t_map *cmap)
{
	if (y <= 0 || y >= cmap->map_y || x <= 0 || x >= cmap->map_x)
		return (INV_MAP);
	else if (ft_fchstr(map[y - 1][x - 1], "01NWES") == 0
		|| ft_fchstr(map[y - 1][x], "01NWES") == 0
		|| ft_fchstr(map[y - 1][x + 1], "01NWES") == 0
		|| ft_fchstr(map[y][x - 1], "01NWES") == 0
		|| ft_fchstr(map[y][x + 1], "01NWES") == 0
		|| ft_fchstr(map[y + 1][x - 1], "01NWES") == 0
		|| ft_fchstr(map[y + 1][x], "01NWES") == 0
		|| ft_fchstr(map[y + 1][x + 1], "01NWES") == 0)
		return (INV_MAP);
	return (0);
}

static int	hero_map(char c, int a, int i, t_map *cmap)
{
	if (cmap->hero != NULL)
		return (INV_MAP);
	cmap->hero = (t_hero *)malloc(1 * sizeof(t_hero));
	cmap->hero->x = i;
	cmap->hero->y = a;
	cmap->hero->px = MAP_S * (i + 0.5);
	cmap->hero->py = MAP_S * (a + 0.5);
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
	return (verify_if_is_inside_walls(cmap->map, a, i, cmap));
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
	if (map[a][i] == 'N' || map[a][i] == 'S' || map[a][i] == 'E'
		|| map[a][i] == 'W')
		return (hero_map(map[a][i], a, i, cmap));
	if (map[a][i] == '0')
		return (verify_if_is_inside_walls(map, a, i, cmap));
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

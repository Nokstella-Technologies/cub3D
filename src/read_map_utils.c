/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:06:21 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/28 19:10:27 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	sprites(char *line, char **map)
{
	char	*tmp;

	if (*map != NULL)
		return (REPEAT_ATR);
	tmp = ft_strtrim(line, " \n");
	free_ptr((void **)&line);
	*map = tmp;
	return (1);
}

static int	colors(char *line, int rgb[3])
{
	char	*tmp;
	char	**t_rgb;

	tmp = ft_strtrim(line, " ");
	free_ptr((void **)&line);
	t_rgb = ft_split(tmp, ',');
	if (t_rgb[0] == NULL || t_rgb[1] == NULL || t_rgb[2] == NULL)
		return (INV_COLOR);
	if (rgb[0] != -1 || rgb[1] != -1 || rgb[2] != -1)
		return (REPEAT_ATR);
	rgb[0] = ft_atoi(t_rgb[0]);
	rgb[1] = ft_atoi(t_rgb[1]);
	rgb[2] = ft_atoi(t_rgb[2]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
		return (INV_COLOR);
	return (1);
}

int	verify_sprite_color(char *line, t_map *map)
{
	if (ft_strncmp(line, "SO", 2) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->so));
	else if (ft_strncmp(line, "NO", 2) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->no));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->we));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->ea));
	else if (ft_strncmp(line, "F", 1) == 0)
		return (colors(ft_substr(line, 1, ft_strlen(line)), (int *)map->floor_c));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (colors(ft_substr(line, 1, ft_strlen(line)), (int *)map->celing_c));
	else if (map->ea && map->no && map->so && map->we && map->floor_c[0] != -1 && map->celing_c[0] != -1)
		return (0);
	else
		return (INV_ATR);
}
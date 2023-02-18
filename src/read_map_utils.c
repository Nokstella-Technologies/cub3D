/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:06:21 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/18 04:54:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	sprites(char *line, char **map)
{
	char	*tmp;

	if (*map != NULL)
	{
		free_ptr((void **)&line);
		return (REPEAT_ATR);
		}
	tmp = ft_strtrim(line, " \n");
	free_ptr((void **)&line);
	*map = tmp;
	return (1);
}

static char	**split_colors(char *tmp)
{
	int		a;
	char	**t_rgb;

	a = -1;
	t_rgb = ft_split(tmp, ',');
	free_ptr((void **)&tmp);
	while(++a < 3)
	{
		tmp = ft_strtrim(t_rgb[a]," ");
		free_ptr((void **)&t_rgb[a]);
		t_rgb[a] = tmp;
	}
	return (t_rgb);
}

static int	colors(char *line, int rgb[3])
{
	char	*tmp;
	char	**t_rgb;
	
	if (rgb[0] != -1 || rgb[1] != -1 || rgb[2] != -1)
	{
		free_ptr((void **)&line);
		return (REPEAT_ATR);
	}
	tmp = ft_strtrim(line, " ");
	free_ptr((void **)&line);
	t_rgb = split_colors(tmp);
	if (t_rgb[0] == NULL || t_rgb[1] == NULL || t_rgb[2] == NULL || t_rgb[3] != NULL)
		return (INV_COLOR);
	rgb[0] = ft_atoi(t_rgb[0]);
	rgb[1] = ft_atoi(t_rgb[1]);
	rgb[2] = ft_atoi(t_rgb[2]);
	free_ptr((void **)&t_rgb[0]);
	free_ptr((void **)&t_rgb[1]);
	free_ptr((void **)&t_rgb[2]);
	free_ptr((void **)&t_rgb);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
		return (INV_COLOR);
	return (1);
}

int	verify_sprite_color(char *line, t_map *map)
{
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->so));
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->no));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->we));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (sprites(ft_substr(line, 2, ft_strlen(line)), &map->ea));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (colors(ft_substr(line, 1, ft_strlen(line)), map->floor_c));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (colors(ft_substr(line, 1, ft_strlen(line)), map->celling_c));
	else if (map->ea && map->no && map->so && map->we && map->floor_c[0] != -1
		&& map->celling_c[0] != -1)
		return (0);
	else
		return (INV_ATR);
}

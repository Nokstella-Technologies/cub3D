/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:08 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/09 17:24:25 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*get_next_atr(int fd)
{
	char	*line;
	char	**splitted;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	splitted = ft_split(line, ' ');
	if (splitted[0] == NULL)
		return (NULL);
	free_ptr((void **)&line);
	free_ptr((void **)&splitted[0]);
	line = splitted[1];
	free_ptr((void **)&splitted);
	return (line);
}

t_map *sprint_colors(int fd)
{
	t_map	*map;

	map = (t_map *)malloc(1 * sizeof(t_map));
	map->no = get_next_atr(fd);
	map->so = get_next_atr(fd);
	map->we = get_next_atr(fd);
	map->ea = get_next_atr(fd);
	ft_printf("NO: %s\n %i", map->no, !map->no);
	// if (map->no || map->so || map->we || map->ea)
	// 	return ();
	return (map);
}

t_game	*read_map(char **argv)
{
	t_game	*game;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(custom_error("File not found", 1));
	game = (t_game *)malloc(1 * sizeof(t_game));
	game->cmap = sprint_colors(fd);
	return (game);
}
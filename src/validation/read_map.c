/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:08 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/10 10:52:53 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



void	verify_sprite(char *line, t_map *map)
{
	if (ft_strncmp(line, "SO", 2) == 0)
		map->so = ft_substr(line, 2, ft_strlen(line));
}

int	sprint_colors(int fd, t_game *game)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while(tmp != NULL)
	{
		if (*tmp != '\n')
		{
			verify_sprite(tmp, game->cmap);
		}
	}
}

t_game	*read_map(char **argv)
{
	t_game	*game;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(custom_error(FD_ERR, 1));
	game = (t_game *)malloc(1 * sizeof(t_game));
	game->cmap = (t_map *)malloc(1 * sizeof(t_map));
	if (game == NULL)
		exit(custom_error(ML_ERR, 1));
	game->err = sprint_colors(fd, game);
	return (game);
}
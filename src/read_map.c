/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:08 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/28 17:23:12 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	add_new_line(t_map *cmap, char *line)
{
	int		a;
	char	**tmp;

	a = 0;
	tmp = (char **)malloc((cmap->map_y + 2) * sizeof(char *));
	tmp[cmap->map_y + 1] = NULL;
	tmp[cmap->map_y] = ft_strtrim(line, "\n");
	a = ft_strlen(line);
	if (cmap->map_x < a)
		cmap->map_x = a;
	a = -1;
	while (++a < cmap->map_y)
		tmp[a] = cmap->map[a];
	if (cmap->map_y != 0)
		free_ptr((void **)&cmap->map);
	cmap->map = tmp;
	cmap->map_y++;
	return (0);
}

int	validation_loop(int fd, t_game *game)
{
	char	*tmp;

	tmp = get_next_line(fd);
	game->cmap->map_x = 0;
	game->cmap->map = NULL;
	game->cmap->map_y = 0;
	while(tmp != NULL)
	{
		if (game->err != 0)
			break ;
		if (*tmp != '\n')
		{
			if (verify_sprite_color(tmp, game->cmap) == 0)
				game->err = add_new_line(game->cmap, tmp);
		}
		free_ptr((void **)&tmp);
		tmp = get_next_line(fd);
	}
	free_ptr((void **)&tmp);
	return (game->err);
}

t_game	*read_map(char **argv)
{
	t_game	*game;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(custom_error("erro de fd", 1));
	game = (t_game *)malloc(1 * sizeof(t_game));
	game->cmap = (t_map *)malloc(1 * sizeof(t_map));
	if (game == NULL || game->cmap == NULL)
		exit(custom_error("erro de malloc", 1));
	game->err = validation_loop(fd, game);
	if (game->err != 0)
		return(NULL);
	return (game);
}
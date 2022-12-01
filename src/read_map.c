/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:08 by llima-ce          #+#    #+#             */
/*   Updated: 2022/12/01 00:16:32 by llima-ce         ###   ########.fr       */
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
	a = ft_strlen(tmp[cmap->map_y]);
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

static void	init_game(t_game *game)
{
	game->err = 0;
	game->cmap->ea = NULL;
	game->cmap->no = NULL;
	game->cmap->so = NULL;
	game->cmap->we = NULL;
	game->cmap->map_x = 0;
	game->cmap->map_y = 0;
	game->cmap->map = NULL;
	game->cmap->celling_c[0] = -1;
	game->cmap->celling_c[1] = -1;
	game->cmap->celling_c[2] = -1;
	game->cmap->floor_c[0] = -1;
	game->cmap->floor_c[1] = -1;
	game->cmap->floor_c[2] = -1;
	game->cmap->hero = NULL;
}

static int	validation_loop(int fd, t_game *game)
{
	char	*tmp;
	int		err;

	tmp = get_next_line(fd);
	while(tmp != NULL)
	{
		if (game->err != 0)
			break ;
		if (*tmp != '\n' )
		{
			err = verify_sprite_color(tmp, game->cmap);
			if (err == 0)
				game->err = add_new_line(game->cmap, tmp);
			else if (err != 1)
				game->err = custom_error(tmp, err);
		}
		else if (game->err == 0)
			game->err = custom_error("map with empty line", INV_MAP);
		free_ptr((void **)&tmp);
		tmp = get_next_line(fd);
	}
	free_ptr((void **)&tmp);
	return (game->err);
}

static void	verify_extension(char *file)
{
	char	*tmp;

	tmp = ft_strrchr(file, '.');
	if (tmp != NULL && ft_strncmp(tmp, ".cub", 5) == 0)
		return ;
	exit(custom_error("file extension wrong", 500));
}

t_game	*read_map(char **argv)
{
	t_game	*game;
	int		fd;

	verify_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(custom_error("On open map file", FD_ERR));
	game = (t_game *)malloc(1 * sizeof(t_game));
	game->cmap = (t_map *)malloc(1 * sizeof(t_map));
	init_game(game);
	if (game == NULL || game->cmap == NULL)
		exit(custom_error("On malloc map and game", MALLOC_ERR));
	else if (validation_loop(fd, game) == 0)
		validation_map_line(game->cmap, game);
	if (game->err != 0)
		clean_all(game);
	return (game);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:01:58 by llima-ce          #+#    #+#             */
/*   Updated: 2022/12/01 15:18:21 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	custom_error(char *error, int err)
{
	if (err == UNKNOWN_ERR)
		ft_printf("Error\n\tUnknown Error: %s\n", error);
	else if (err == MALLOC_ERR)
		ft_printf("Error\n\tMalloc Error: %s\n", error);
	else if (err == FD_ERR)
		ft_printf("Error\n\tFD Error: %s\n", error);
	else if (err == INV_ATR)
		ft_printf("Error\n\tInvalid Atribbute: %s\n", error);
	else if (err == INV_COLOR)
		ft_printf("Error\n\tInvalid Color: %s\n", error);
	else if (err == REPEAT_ATR)
		ft_printf("Error\n\tRepeat Atribbute: %s\n", error);
	else if (err == INV_MAP)
		ft_printf("Error\n\tInvalid Map Costruction: %s\n", error);
	else if (err == GAME_LOAD)
		ft_printf("Error\n\tErro on start the game: %s\n", error);
	else
		ft_printf("Error\n%s\n", error);
	return (err);
}

int		close_all(t_game *game)
{
	clean_all(game);
	return(0);
}

void	clean_all(t_game *game)
{
	int	err;

	err = game->err;
	free_ptr((void **)&game->cmap->no);
	free_ptr((void **)&game->cmap->so);
	free_ptr((void **)&game->cmap->we);
	free_ptr((void **)&game->cmap->ea);
	free_ptr((void **)&game->cmap->hero);
	while (game->cmap->map != NULL && --game->cmap->map_y >= 0)
		free_ptr((void **)&game->cmap->map[game->cmap->map_y]);
	free_ptr((void **)&game->cmap->map);
	free_ptr((void **)&game->cmap);
	mlx_destroy_image(game->mlx, game->sprite->ea);
	mlx_destroy_image(game->mlx, game->sprite->no);
	mlx_destroy_image(game->mlx, game->sprite->so);
	mlx_destroy_image(game->mlx, game->sprite->we);
	free_ptr((void **)&game->sprite);
	free_ptr((void **)&game->move);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_ptr((void **)&game->mlx);
	free_ptr((void **)&game);
	exit(err);
}
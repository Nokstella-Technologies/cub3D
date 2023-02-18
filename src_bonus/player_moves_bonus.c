/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:17:17 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/17 19:50:27 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cam_rotation(t_game *game)
{
	if (game->move->rot_r == TRUE)
	{
		game->hero->pa -= ROT_SP;
		game->hero->pa = fix_ang(game->hero->pa);
		game->hero->pdx = cos(deg_to_rad(game->hero->pa));
		game->hero->pdy = -sin(deg_to_rad(game->hero->pa));
	}
	if (game->move->rot_l == TRUE)
	{
		game->hero->pa += ROT_SP;
		game->hero->pa = fix_ang(game->hero->pa);
		game->hero->pdx = cos(deg_to_rad(game->hero->pa));
		game->hero->pdy = -sin(deg_to_rad(game->hero->pa));
	}
}

int	collision(float p, float pd, t_bool is_sub)
{
	int	o;

	if (pd < 0)
		o = -20;
	else
		o = 20;
	if (is_sub == TRUE)
		return ((int)((p / MAP_S + (pd - o) / MAP_S)));
	else
		return ((int)((p / MAP_S + (pd + o) / MAP_S)));
}

void	move_front_back(t_game *game)
{
	if (game->move->w == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdx, FALSE)]
			!= '1')
			game->hero->px += game->hero->pdx * MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdy, FALSE)]
			[game->hero->x] != '1')
			game->hero->py += game->hero->pdy * MOVE_SP;
	}
	if (game->move->s == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdx, TRUE)]
			!= '1')
			game->hero->px -= game->hero->pdx * MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdy, TRUE)]
			[game->hero->x] != '1')
			game->hero->py -= game->hero->pdy * MOVE_SP;
	}
}

void	move_right_left(t_game *game)
{
	if (game->move->d == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdy, TRUE)] != '1')
			game->hero->px -= game->hero->pdy * MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdx, FALSE)]
			[game->hero->x] != '1')
			game->hero->py += game->hero->pdx * MOVE_SP;
	}
	if (game->move->a == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdy, FALSE)]
			!= '1')
			game->hero->px += game->hero->pdy * MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdx, TRUE)]
			[game->hero->x] != '1')
			game->hero->py -= game->hero->pdx * MOVE_SP;
	}
}

void	move_player(t_game *game)
{
	move_front_back(game);
	move_right_left(game);
}

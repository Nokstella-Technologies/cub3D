/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:15:10 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 11:23:09 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	horizontal_ray_check(t_game *game, t_ray *ray)
{
	if (cos(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->rx = (((int)game->hero->px >> 6) << 6) + 64;
		ray->ry = (game->hero->px - ray->rx) * ray->tan + game->hero->py;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->tan;
		ray->eye_v = 'E';
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->rx = (((int)game->hero->px >> 6) << 6) - 0.0001;
		ray->ry = (game->hero->px - ray->rx) * ray->tan + game->hero->py;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->tan;
		ray->eye_v = 'W';
	}
	else
	{
		ray->rx = game->hero->px;
		ray->ry = game->hero->py;
		ray->dof = game->cmap->map_x;
	}
}

void	vertical_ray_check(t_game *game, t_ray *ray)
{
	if (sin(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->ry = (((int)game->hero->py >> 6) << 6) - 0.0001;
		ray->rx = (game->hero->py - ray->ry) * ray->tan + game->hero->px;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->tan;
		ray->eye_h = 'N';
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->ry = (((int)game->hero->py >> 6) << 6) + 64;
		ray->rx = (game->hero->py - ray->ry) * ray->tan + game->hero->px;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->tan;
		ray->eye_h = 'S';
	}
	else
	{
		ray->rx = game->hero->px;
		ray->ry = game->hero->py;
		ray->dof = game->cmap->map_y;
	}
}

void	horizontal_ray_dist(t_game *game, t_ray *ray)
{
	while (ray->dof < game->cmap->map_x || ray->dof < game->cmap->map_y)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * game->cmap->map_x + ray->mx;
		if (ray->mp > 0 && ray->my >= 0 && ray->my < game->cmap->map_y
			&& ray->mx >= 0 && ray->mx < game->cmap->map_x
			&& game->cmap->map[ray->my][ray->mx] == '1')
		{
			ray->dof = game->cmap->map_x;
			ray->dis_v = cos(deg_to_rad(ray->ra)) * (ray->rx - game->hero->px)
				- sin(deg_to_rad(ray->ra)) * (ray->ry - game->hero->py);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	vertical_ray_dist(t_game *game, t_ray *ray)
{
	while (ray->dof < game->cmap->map_y)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * game->cmap->map_x + ray->mx;
		if (ray->mp > 0 && ray->my >= 0 && ray->my < game->cmap->map_y
			&& ray->mx >= 0 && ray->mx < game->cmap->map_x
			&& game->cmap->map[ray->my][ray->mx] == '1')
		{
			ray->dof = game->cmap->map_y;
			ray->dis_h = cos(deg_to_rad(ray->ra)) * (ray->rx - game->hero->px)
				- sin(deg_to_rad(ray->ra)) * (ray->ry - game->hero->py);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	calculate_ray_wall_height(t_game *game, t_ray *ray, t_ray_print *draws)
{
	draws->shade = 1;
	if (ray->dis_v < ray->dis_h)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		draws->shade = 0.5;
		ray->dis_h = ray->dis_v;
		ray->eye_h = ray->eye_v;
	}
	draws->ca = fix_ang(game->hero->pa - ray->ra);
	ray->dis_h = ray->dis_h * cos(deg_to_rad(draws->ca));
	draws->line_h = (MAP_S * 600) / (ray->dis_h);
	draws->ty_step = 64.0 / (float)draws->line_h;
	draws->ty_off = 0;
	if (draws->line_h > 600)
	{
		draws->ty_off = (draws->line_h - 600) / 2.0;
		draws->line_h = 600;
	}
	draws->line_off = 300 - (draws->line_h >> 1);
}

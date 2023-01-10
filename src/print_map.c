/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:51:21 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 11:39:46 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void draw_floor_celing(t_game *game, t_ray *ray,t_ray_print *draws)
{

	draw_line(game, (int [2]) {ray->r, 0}, (int [2]){ray->r, draws->line_off}, create_trgb(255, game->cmap->floor_c[0],  game->cmap->floor_c[1],  game->cmap->floor_c[2]));
	draw_line(game, (int [2]) {ray->r, draws->line_off + draws->line_h}, (int [2]){ray->r, 600},create_trgb(255, game->cmap->celling_c[0],  game->cmap->celling_c[1],  game->cmap->celling_c[2]));
	
}

void	draw_wall(t_game *game, t_ray *ray, t_ray_print *draws)
{
	int		y;

	draws->ty = draws->ty_off * draws->ty_step;
	if (draws->shade==1)
	{
		draws->tx = (int)(ray->rx )% 64;
		if (ray->ra > 180)
			draws->tx = 63 - draws->tx;
		}
		else
		{
			draws->tx = (int)(ray->ry)%64;
			if (ray->ra>90 && ray->ra<270)
				draws->tx = 63- draws->tx;
		}
		y = -1;
		while (++y < draws->line_h)
		{
			draws->color = ((int)(draws->ty) * 64 + (int)(draws->tx)) * 4;
			if (ray->eye_h == 'N')
				draws->color = get_sprite_color(draws->color,
					game->sprite->no->dump, draws->shade);
			if (ray->eye_h == 'E')
				draws->color = get_sprite_color(draws->color,
					game->sprite->ea->dump, draws->shade);
			if (ray->eye_h == 'W')
				draws->color = get_sprite_color(draws->color,
					game->sprite->we->dump, draws->shade);
			if (ray->eye_h == 'S')
				draws->color = get_sprite_color(draws->color,
					game->sprite->so->dump, draws->shade);
			my_mlx_pixel_put(game->img, ray->r, draws->line_off + y,
				draws->color);
			draws->ty += draws->ty_step;
		}
}

void	drawRays2D(t_game *game)
{
	t_ray_print	draws;
	t_ray		ray;

	ray.ra = fix_ang(game->hero->pa + 35);
	ray.xo = 0;
	ray.yo = 0;
	ray.r = -1;
	while (++ray.r < 800)
	{
		ray.dof=0; 
		ray.dis_v=100000;
		ray.tan = tan(deg_to_rad(ray.ra));
		horizontal_ray_check(game, &ray);
		horizontal_ray_dist(game, &ray);
		ray.vx = ray.rx;
		ray.vy = ray.ry;
		ray.dof = 0;
		ray.dis_h = 100000;
		ray.tan = 1.0 / ray.tan;
		vertical_ray_check(game, &ray);
		vertical_ray_dist(game, &ray);
		calculate_ray_wall_height(game, &ray, &draws);
		draw_floor_celing(game, &ray, &draws);
		draw_wall(game, &ray, &draws);
		ray.ra = fix_ang(ray.ra - 0.0875);//go to next ray
	}
}



int	print_mini_map(t_game *game)
{

	drawRays2D(game);
	draw_mini_map(game, 10, 10, 10);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
	move_player(game);
	game->hero->x = (int) game->hero->px / MAP_S;
	game->hero->y = (int) game->hero->py / MAP_S;
	cam_rotation(game);
	return (0);
}
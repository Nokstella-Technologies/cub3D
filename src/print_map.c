/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:51:21 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/06 11:21:11 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	drawRays2D(t_game *game)
{
	t_ray	ray;

	ray.ra = fix_ang(game->hero->pa + 35);
	ray.xo = 0;
	ray.yo = 0;
	ray.r = -1;
	while (++ray.r < 800)
	{
		ray.dof=0; 
		ray.dis_v=100000;
		ray.tan = tan(deg_to_rad(ray.ra));
		if (cos(deg_to_rad(ray.ra)) > 0.001)
		{
			ray.rx=(((int)game->hero->px>>6)<<6)+64;
			ray.ry=(game->hero->px-ray.rx)*ray.tan+game->hero->py; ray.xo= 64;
			ray.yo=-ray.xo*ray.tan;
			ray.eye_v = 'E';
		}//looking left
		else if (cos(deg_to_rad(ray.ra)) < -0.001)
		{
			ray.rx=(((int)game->hero->px>>6)<<6) -0.0001;
			ray.ry=(game->hero->px-ray.rx)*ray.tan+game->hero->py; ray.xo=-64;
			ray.yo=-ray.xo*ray.tan;
			ray.eye_v = 'W';
		}//looking right
		else
		{
			ray.rx=game->hero->px;
			ray.ry=game->hero->py;
			ray.dof = game->cmap->map_x;
		}//looking up or down. no hit  
		while(ray.dof < game->cmap->map_x || ray.dof < game->cmap->map_y)
		{
			ray.mx = (int)(ray.rx)>>6;
			ray.my = (int)(ray.ry)>>6;
			ray.mp=ray.my*game->cmap->map_x+ray.mx;
			// ft_printf("horizontal ray.mx = %d ray.my = %d ray.mp = %d\n",ray.mx,ray.my,ray.mp);
			if (ray.mp > 0 && ray.my >= 0 && ray.my < game->cmap->map_y && ray.mx >= 0 && ray.mx < game->cmap->map_x && game->cmap->map[ray.my][ray.mx] == '1')
			{
				ray.dof = game->cmap->map_x;
				ray.dis_v = cos(deg_to_rad(ray.ra)) * (ray.rx - game->hero->px) - sin(deg_to_rad(ray.ra)) * (ray.ry - game->hero->py);
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}     //check next horizontal
		}
		ray.vx = ray.rx;
		ray.vy = ray.ry;
		//---Horizontal---
		ray.dof = 0;
		ray.dis_h = 100000;
		ray.tan = 1.0 / ray.tan;
		if (sin(deg_to_rad(ray.ra)) > 0.001)
		{
			ray.ry = (((int)game->hero->py>>6)<<6) - 0.0001;
			ray.rx = (game->hero->py - ray.ry) * ray.tan + game->hero->px;
			ray.yo = - 64;
			ray.xo = -ray.yo * ray.tan;
			ray.eye_h = 'N';
		}//looking up 
		else if (sin(deg_to_rad(ray.ra)) < -0.001)
		{
			ray.ry = (((int)game->hero->py>>6)<<6) + 64;
			ray.rx = (game->hero->py - ray.ry) * ray.tan + game->hero->px;
			ray.yo = 64; ray.xo = -ray.yo * ray.tan;
			ray.eye_h = 'S';
		}//looking down
		else
		{
			ray.rx = game->hero->px;
			ray.ry = game->hero->py;
			ray.dof = game->cmap->map_y;
		}//looking straight left or right
		while (ray.dof < game->cmap->map_y)
		{
			ray.mx = (int)(ray.rx)>>6;
			ray.my = (int)(ray.ry)>>6;
			ray.mp=ray.my*game->cmap->map_x+ray.mx;
			// ft_printf("vertical ray.mx = %d ray.my = %d ray.mp = %d\n",ray.mx,ray.my,ray.mp);
			if (ray.mp > 0 && ray.my >= 0 && ray.my < game->cmap->map_y && ray.mx >= 0 && ray.mx < game->cmap->map_x && game->cmap->map[ray.my][ray.mx] == '1')
			{
				ray.dof = game->cmap->map_y;
				ray.dis_h = cos(deg_to_rad(ray.ra)) * (ray.rx-game->hero->px) - sin(deg_to_rad(ray.ra)) * (ray.ry - game->hero->py);
			}//hit         
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}//check next horizontal
		}

		// calcula altura e tamanho para printar o raio de visao na tela
		  float shade=1;
		if (ray.dis_v < ray.dis_h)
		{
			ray.rx=ray.vx;
			ray.ry=ray.vy;
			shade=0.5;
			ray.dis_h=ray.dis_v;
			ray.eye_h=ray.eye_v;
		}
		int ca = fix_ang(game->hero->pa - ray.ra);
		ray.dis_h = ray.dis_h * cos(deg_to_rad(ca));//fix fisheye 
		int lineH = (MAP_S*600)/(ray.dis_h);
		double	ty_step=64.0/(float)lineH;
		float ty_off = 0;
		if(lineH>600)
		{
			ty_off=(lineH-600)/2.0;
			lineH=600;
		}
		int lineOff = 300 - (lineH>>1);//line offset

		
		draw_line(game, (int [2]) {ray.r, 0}, (int [2]){ray.r, lineOff}, create_trgb(255, game->cmap->floor_c[0],  game->cmap->floor_c[1],  game->cmap->floor_c[2]));
		draw_line(game, (int [2]) {ray.r, lineOff + lineH}, (int [2]){ray.r, 600},create_trgb(255, game->cmap->celling_c[0],  game->cmap->celling_c[1],  game->cmap->celling_c[2]));
		
		
		//draw vertical wall
		int		y;
		double	ty = ty_off * ty_step;
		double	tx;
		if (shade==1)
		{
			tx = (int)(ray.rx )% 64;
			if (ray.ra > 180)
				tx = 63 - tx;
		}
		else
		{
			tx = (int)(ray.ry)%64;
			if (ray.ra>90 && ray.ra<270)
				tx = 63-tx;
		}
		for (y=0;y<lineH;y++)
		{
			int	color = ((int)(ty) * 64 + (int)(tx)) * 4;
			if (ray.eye_h == 'N')
				color = get_sprite_color(color, game->sprite->no->dump, shade);
			if (ray.eye_h == 'E')
				color = get_sprite_color(color, game->sprite->ea->dump, shade);
			if (ray.eye_h == 'W')
				color = get_sprite_color(color, game->sprite->we->dump, shade);
			if (ray.eye_h == 'S')
				color = get_sprite_color(color, game->sprite->so->dump, shade);
			my_mlx_pixel_put(game->img, ray.r, lineOff + y, color);
			ty += ty_step;
		}
		ray.ra = fix_ang(ray.ra - 0.0875);//go to next ray
	}
}


void	move(t_game *game)
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
		game->hero->pdy=-sin(deg_to_rad(game->hero->pa));
	}
}

int	collision(float p,float pd, t_bool is_sub)
{
	int	o;

	if (pd < 0)
		o = -20;
	else
		o = 20;
	if (is_sub == TRUE)
		return ((int)((p/MAP_S + (pd-o)/ MAP_S)));
	else
		return ((int)((p/MAP_S + (pd+o)/ MAP_S)));
}

void	move_forward(t_game *game)
{
	if(game->move->w == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdx, FALSE)]
			!= '1')
			game->hero->px += game->hero->pdx * MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdy, FALSE)]
			[game->hero->x] != '1')
			game->hero->py += game->hero->pdy * MOVE_SP;
	}
	//move backwards if no wall behind ray.you
	if(game->move->s == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdx, TRUE)]
			!= '1')
			game->hero->px -= game->hero->pdx * MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdy, TRUE)]
			[game->hero->x] != '1')
			game->hero->py -= game->hero->pdy * MOVE_SP;
	}
	if(game->move->d == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdy, TRUE)]
			!= '1')
			game->hero->px -= game->hero->pdy  *  MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdx, FALSE)]
			[game->hero->x] != '1')
			game->hero->py += game->hero->pdx  * MOVE_SP;
	}
	if(game->move->a == TRUE)
	{
		if (game->cmap->map[game->hero->y]
			[collision(game->hero->px, game->hero->pdy, FALSE)]
			!= '1')
			game->hero->px += game->hero->pdy  *  MOVE_SP;
		if (game->cmap->map[collision(game->hero->py, game->hero->pdx, TRUE)]
			[game->hero->x] != '1')
			game->hero->py -= game->hero->pdx  * MOVE_SP;
	}
}

int	print_mini_map(t_game *game)
{

	drawRays2D(game);
	draw_mini_map(game, 10, 10);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
	move_forward(game);
	game->hero->x = (int) game->hero->px / MAP_S;
	game->hero->y = (int) game->hero->py / MAP_S;
	move(game);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:51:21 by llima-ce          #+#    #+#             */
/*   Updated: 2022/12/01 19:11:09 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void	drawRays2D(t_game *game)
{
	int		r,mx,my,mp,dof;
	float	rx,ry,ra,xo = 0,yo = 0,vx,vy,disV,disH;
	char	eyeV, eyeH;

	ra = fix_ang(game->hero->pa + 30);
	for (r = 0; r < 800; r++)
	{
		dof=0; 
		disV=100000;
		float Tan = tan(deg_to_rad(ra));
		if (cos(deg_to_rad(ra)) > 0.001)
		{
			rx=(((int)game->hero->px>>6)<<6)+64;
			ry=(game->hero->px-rx)*Tan+game->hero->py; xo= 64;
			yo=-xo*Tan;
			eyeV = 'W';
		}//looking left
		else if (cos(deg_to_rad(ra)) < -0.001)
		{
			rx=(((int)game->hero->px>>6)<<6) -0.0001;
			ry=(game->hero->px-rx)*Tan+game->hero->py; xo=-64;
			yo=-xo*Tan;
			eyeV = 'E';
		}//looking right
		else
		{
			rx=game->hero->px;
			ry=game->hero->py;
			dof = game->cmap->map_x;
		}//looking up or down. no hit  
		while(dof < game->cmap->map_x || dof < game->cmap->map_y)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp=my*game->cmap->map_x+mx;
			// ft_printf("horizontal mx = %d my = %d mp = %d\n",mx,my,mp);
			if (mp > 0 && my >= 0 && my < game->cmap->map_y && mx >= 0 && mx < game->cmap->map_x && game->cmap->map[my][mx] == '1')
			{
				dof = game->cmap->map_x;
				disV = cos(deg_to_rad(ra)) * (rx - game->hero->px) - sin(deg_to_rad(ra)) * (ry - game->hero->py);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}     //check next horizontal
		}
		vx = rx;
		vy = ry;
		//---Horizontal---
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(deg_to_rad(ra)) > 0.001)
		{
			ry = (((int)game->hero->py>>6)<<6) - 0.0001;
			rx = (game->hero->py - ry) * Tan + game->hero->px;
			yo = - 64;
			xo = -yo * Tan;
			eyeH = 'N';
		}//looking up 
		else if (sin(deg_to_rad(ra)) < -0.001)
		{
			ry = (((int)game->hero->py>>6)<<6) + 64;
			rx = (game->hero->py - ry) * Tan + game->hero->px;
			yo= 64; xo = -yo * Tan;
			eyeH = 'S';
		}//looking down
		else
		{
			rx = game->hero->px;
			ry = game->hero->py;
			dof = game->cmap->map_y;
		}//looking straight left or right
		while (dof < game->cmap->map_y)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp=my*game->cmap->map_x+mx;
			// ft_printf("vertical mx = %d my = %d mp = %d\n",mx,my,mp);
			if (mp > 0 && my >= 0 && my < game->cmap->map_y && mx >= 0 && mx < game->cmap->map_x && game->cmap->map[my][mx] == '1')
			{
				dof = game->cmap->map_y;
				disH = cos(deg_to_rad(ra)) * (rx-game->hero->px) - sin(deg_to_rad(ra)) * (ry - game->hero->py);
			}//hit         
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}//check next horizontal
		}
		if (disV < disH)
		{
			rx=vx;
			ry=vy;
			disH=disV;
			eyeH=eyeV;
		}
		int ca = fix_ang(game->hero->pa - ra);
		disH = disH * cos(deg_to_rad(ca));//fix fisheye 
		int lineH = (MAP_S*600)/(disH);
		if (lineH>600)
			lineH=600;//line height and limit
		int lineOff = 300 - (lineH>>1);//line offset
		//draw vertical wall
		draw_line(game, (int [2]) {r, 0}, (int [2]){r, lineOff}, create_trgb(255, game->cmap->floor_c[0],  game->cmap->floor_c[1],  game->cmap->floor_c[2]));
		draw_line(game, (int [2]) {r, lineOff + lineH}, (int [2]){r, 600},create_trgb(255, game->cmap->celling_c[0],  game->cmap->celling_c[1],  game->cmap->celling_c[2]));
		int color = 0x000000;
		if (eyeH == 'N')
			color = 0xAF0000;
		if (eyeH == 'E')
			color = 0x00AF00;
		if (eyeH == 'W')
			color = 0x0000AF;
		if (eyeH == 'S')
			color = 0xAFAF00;
		draw_line(game, (int [2]) {r, lineOff}, (int [2]){r, lineOff + lineH}, color);
		ra = fix_ang(ra - 0.075);//go to next ray
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
	//move backwards if no wall behind you
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
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	move_forward(game);
	game->hero->x = (int) game->hero->px / MAP_S;
	game->hero->y = (int) game->hero->py / MAP_S;
	move(game);
	return (0);
}
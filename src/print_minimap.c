/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:51:21 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/30 02:12:00 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



// float distance(int ax,ay,bx,by,ang){ return cos(DEGTORAD(ang))*(bx-ax)-sin(DEGTORAD(ang))*(by-ay);}

void	drawRays2D(t_game *game)
{
	int		r,mx,my,mp,dof,side;
	float	vx,vy,rx,ry,ra,xo,yo,disV,disH;

	ra = fix_ang(game->hero->pa + 30);
	for (r=0; r<60; r++)
	{
		dof=0; side=0; disV=100000;
		float Tan = tan(DEGTORAD(ra));
		if (cos(DEGTORAD(ra)) > 0.001)
		{
			rx=(((int)game->hero->px>>6)<<6)+64;
			ry=(game->hero->px-rx)*Tan+game->hero->py; xo= 64;
			yo=-xo*Tan;
		}//looking left
		else if (cos(DEGTORAD(ra)) < -0.001)
		{
			rx=(((int)game->hero->px>>6)<<6) -0.0001;
			ry=(game->hero->px-rx)*Tan+game->hero->py; xo=-64;
			yo=-xo*Tan;
		}//looking right
		else
		{
			rx=game->hero->px;
			ry=game->hero->py;
			dof=8;
		}//looking up or down. no hit  
		while(dof<8)
		{
			mx=(int)(rx)>>6;
			my=(int)(ry)>>6;
			mp=my*game->cmap->map_x+mx;
			if (mp > 0 && mp < game->cmap->map_x * game->cmap->map_y && game->cmap->map[mp] == 1)
			{
				dof = 8;
				disV = cos(DEGTORAD(ra)) * (rx - game->hero->px) - sin(DEGTORAD(ra))
				* (ry-game->hero->py);
			}//hit         
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
		if (sin(DEGTORAD(ra)) > 0.001)
		{
			ry = (((int)game->hero->py>>6)<<6) - 0.0001;
			rx = (game->hero->py - ry) * Tan + game->hero->px;
			yo = - 64;
			xo = -yo * Tan;
		}//looking up 
		else if (sin(DEGTORAD(ra)) < -0.001)
		{
			ry = (((int)game->hero->py>>6)<<6) + 64;
			rx = (game->hero->py - ry) * Tan + game->hero->px;
			yo= 64; xo = -yo * Tan;
		}//looking down
		else
		{
			rx = game->hero->px;
			ry = game->hero->py;
			dof = 8;
		}//looking straight left or right
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * game->cmap->map_x + mx;
			if(mp > 0 && mp < game->cmap->map_x * game->cmap->map_y && game->cmap->map[mp] == 1)
			{
				dof=8;
				disH = cos(DEGTORAD(ra)) * (rx-game->hero->px) - sin(DEGTORAD(ra))
				* (ry - game->hero->py);
			}//hit         
			else
			{
				rx+=xo;
				ry+=yo;
				dof+=1;
			}//check next horizontal
		}
		glColor3f(0,0.8,0);
		if (disV < disH)
		{
			rx=vx;
			ry=vy;
			disH=disV;
			draw_line(game, (int [2]) {px , rx}, (int [2]){py, ry},0xFF0000 )
		}
		else
		{
			draw_line(game, (int [2]) {px , rx}, (int [2]){py, ry},0x00FF00 )
		}
// 		int ca = FixAng(game->hero->pa-ra);
// 		disH = disH * cos(DEGTORAD(ca));//fix fisheye 
// 		int lineH = (mapS*320)/(disH);
// 		if (lineH>320)
// 			lineH=320;//line height and limit
// 		int lineOff = 160 - (lineH>>1);//line offset
// //draw vertical wall  

//   ra=FixAng(ra-1);                                                              //go to next ray
 }


void draw_player2d(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	printf("px = %0.2f py = %0.2f pdx = %0.2f pdy = %0.2f\n", game->hero->px, game->hero->py, game->hero->pdx, game->hero->pdy);
	while (++i < 6)
	{
		j = -1;
		while (++j < 6)
			mlx_pixel_put(game->mlx, game->win, game->hero->px + i,
			game->hero->py + j, 0xFF0000);
			
	}
}

void	print_mini_map(t_game *game)
{
	int	a;
	int	b;
	int	xy[2];

	a = game->cmap->hero->y - 5;
	if (a < 0)
		a = 0;
	xy[1] = 20;
	while(++a < game->cmap->hero->y + 5 && a < game->cmap->map_y)
	{
		xy[0] = 20;
		b = game->cmap->hero->x - 5;
		if (b < 0)
			b = 0;
		while(++b < game->cmap->hero->x + 5 && b < (int)LEN(game->cmap->map[a]))
		{
			if (game->cmap->map[a][b] == '1')
				square(game, xy[0], xy[1], 0x003417);
			else if (game->cmap->map[a][b] != ' ')
				square(game, xy[0], xy[1], 0xFFFFFF);
			xy[0] += 20;
		}
		xy[1] += 20;
	}
	draw_player2d(game);

}
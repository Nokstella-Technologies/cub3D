/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:29 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/07 13:09:52 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("Hello from key_hook! %i \n", keycode);
	return (0); 
}

void print_sprint(t_vars *vars, int x, int y, void *img)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	square(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 5)
			my_mlx_pixel_put(img, x + i, y + j, color);
	}
}

void	triangle(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 5)
		{
			if (i == 0 || i == 4)
				my_mlx_pixel_put(img, x + i, y + j, color);
			else if (j == 0 || j == 4) 
				my_mlx_pixel_put(img, x + i, y + j, color);
		}
	}
}

void	mini_map(t_data *img)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	y = 5;
	while (++i < 5)
	{
		j = -1;
		x = 5;
		while (++j < 5)
		{
			if (map[i][j] == '1')
				square(img, x, y, 0x00FFFFFF);
			else if (map[i][j] == 'N')
				triangle(img, x, y, 0x00FFFFFF);
			x += 7;
		}
		y += 7;
	}
}



int	main(int argc,char **argv)
{
	t_vars	vars;
	// void	*img1;
	// int		x;
	t_data	img;
	
	(void) argv;
	if(argc == 1) {
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 800, 600, "Hello world!");
		// img1 = mlx_xpm_file_to_image(vars.mlx, relative_path, &x, &x);
		img.img = mlx_new_image(vars.mlx, 600, 600);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
		mini_map(&img);
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
		mlx_key_hook(vars.win, key_hook, &vars);
		mlx_loop(vars.mlx);
	}
}

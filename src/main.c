/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:29 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/03 17:26:51 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("Hello from key_hook! %i \n", keycode);
	return (0); 
}

void print_map(t_vars *vars)
{
	
}

int	main(int argc,char **argv)
{
	t_vars	vars;
	
	(void) argv;
	if(argc == 1) {
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
		print_map(vars);
		mlx_key_hook(vars.win, key_hook, &vars);
		mlx_loop(vars.mlx);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:29 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/18 21:21:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (argc == 2)
	{
		game = read_map(argv);
		start_game(game);
		close_all(game);
	}
}

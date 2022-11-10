/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:01:58 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/09 17:38:11 by llima-ce         ###   ########.fr       */
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
	ft_printf("Error\n%s", error);
	return (err);
}

void	*clean_map(t_map *map, int a)
{
	free_ptr((void **)&map->no);
	free_ptr((void **)&map->so);
	free_ptr((void **)&map->we);
	free_ptr((void **)&map->ea);
	a = -1;
	while (map->map != NULL && map->map[++a] != NULL)
		free_ptr((void **)&map->map[a]);
	free_ptr((void **)&map->map);
	return (NULL);
}
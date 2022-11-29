/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:01:58 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/28 19:25:16 by llima-ce         ###   ########.fr       */
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
	if (err == UNKNOWN_ERR)
		ft_printf("Error\n\tUnknown Error: %s\n", error);
	else if (err == MALLOC_ERR)
		ft_printf("Error\n\tMalloc Error: %s\n", error);
	else if (err == FD_ERR)
		ft_printf("Error\n\tFD Error: %s\n", error);
	else if (err == INV_ATR)
		ft_printf("Error\n\tInvalid Atribbute: %s\n", error);
	else if (err == INV_COLOR)
		ft_printf("Error\n\tInvalid Color: %s\n", error);
	else if (err == REPEAT_ATR)
		ft_printf("Error\n\tRepeat Atribbute: %s\n", error);
	else if (err == 513)
		ft_printf("Error\n\tWrong Map: %s\n", error);
	else
		ft_printf("Error\n%s\n", error);
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
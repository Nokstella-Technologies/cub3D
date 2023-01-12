/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:59:00 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/12 19:20:00 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

float	fix_ang(float a)
{
	if ((int)a > 359.9)
		return (a - 360);
	if ((int)a < 0.9)
		return (a + 360);
	return (a);
}

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

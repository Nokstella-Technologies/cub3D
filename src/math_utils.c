/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:59:00 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 11:35:23 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

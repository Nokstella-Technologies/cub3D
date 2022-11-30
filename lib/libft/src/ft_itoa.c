/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 21:51:57 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/28 17:30:17 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_size(long int n)
{
	if (n < 0)
		return (1 + ft_count_size(-n));
	if (n <= 9)
		return (1);
	else
		return (1 + ft_count_size(n / 10));
}

static void	ft_populete_loop(char *lnew, int n, int size)
{
	if (n < 0)
	{
		lnew[0] = '-';
		n *= -1;
	}
	if (n > 9)
		ft_populete_loop(lnew, n / 10, size - 1);
	lnew[size] = (n % 10) + 48;
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*int_str;
	int		flag;

	flag = 0;
	if (n <= INT_MIN)
	{
		n = -INT_MAX;
		flag = 1;
	}
	size = ft_count_size(n);
	int_str = (char *)malloc(size + 1 * sizeof(char));
	int_str[size] = 0;
	if (!int_str)
		return (NULL);
	ft_populete_loop(int_str, n, --size);
	if (flag == 1)
		int_str[size] += flag;
	return (int_str);
}

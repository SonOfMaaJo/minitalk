/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 22:02:07 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/15 23:32:29 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_lenp(int n)
{
	int	i;

	i = 1;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while ((n = n / 10) != 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*nchar;
	int		len;

	i = 0;
	len = ft_lenp(n);
	nchar = (char *)malloc(sizeof(char) * (len + 1));
	if (nchar != NULL)
	{
		i = 0;
		nchar[len] = '\0';
		if (n == INT_MIN)
		{
			nchar[len-- - 1] = '8';
			n /= 10;
		}
		if (n < 0)
		{
			nchar[0] = '-';
			n *= -1;
		}
		if (n == 0)
			nchar[0] = '0';
		while (n != 0)
		{
			nchar[len - i++ - 1] = n % 10 + '0';
			n = n / 10;
		}
	}
	return (nchar);
}

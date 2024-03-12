/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:49:44 by midbella          #+#    #+#             */
/*   Updated: 2024/03/04 21:28:12 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static size_t	total_len(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i = 2;
		n = n * -1;
	}
	if (n < 10 && n >= 0)
		return (i);
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = total_len(n);
	str = malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	str[len] = '\0';
	len--;
	while (n >= 10)
	{
		str[len--] = (n % 10) + 48;
		n = n / 10;
	}
	str[len] = n + 48;
	return (str);
}

int	print_nb(int nb)
{
	long	n;
	char	s[10];
	int		j;
	int		tot;

	tot = 0;
	n = nb;
	if (n < 0)
	{
		tot += write(1, "-", 1);
		n = n * -1;
	}
	j = 0;
	while (n >= 10)
	{
		s[j] = (n % 10) + 48;
		n = n / 10;
		j++;
	}
	s[j] = n + 48;
	while (j >= 0)
		tot += write(1, &s[j--], 1);
	return (tot);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:49:05 by midbella          #+#    #+#             */
/*   Updated: 2024/03/12 16:33:09 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str)
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (res == NULL)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	ls1;
	size_t	ls2;
	char	*res;
	int		i;
	int		y;

	y = 0;
	i = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (res == NULL)
		return (NULL);
	res[ls1 + ls2] = '\0';
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[y] != '\0')
		res[i++] = s2[y++];
	return (res);
}

char	*scaner(char *file)
{
	int		r;
	int		fd;
	char	*map;
	char	*temp;
	char	buff[6];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	r = read(fd, buff, 5);
	map = NULL;
	while (r)
	{
		buff[r] = 0;
		temp = map;
		map = ft_strjoin(map, buff);
		free(temp);
		if (map == NULL)
			return (NULL);
		r = read(fd, buff, 5);
	}
	return (map);
}

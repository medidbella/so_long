/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:30:42 by midbella          #+#    #+#             */
/*   Updated: 2024/02/23 17:16:35 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	filler(t_ints *vars, char *map)
{
	int	arr[5];
	int	i;

	i = 0;
	arr[4] = 0;
	arr[0] = vars->i + 1;
	arr[1] = vars->i - 1;
	arr[2] = vars->i - (vars->x + 1);
	arr[3] = vars->i + (vars->x + 1);
	while (i <= 3)
	{
		if (map[arr[i]] == '0' || map[arr[i]] == 'C'
			|| map[arr[i]] == 'E')
		{
			map[arr[i]] = 'S';
			arr[4] = 1;
		}
		i++;
	}
	return (arr[4] == 1);
}

static int	checker_4(char *map, t_ints vars)
{
	int	r;

	vars.i = vars.p;
	filler(&vars, map);
	vars.y = 0;
	while (1)
	{
		vars.i = vars.x + 1;
		r = 0;
		while (map[vars.i])
		{
			if (map[vars.i] == 'S')
				r += filler(&vars, map);
			vars.i++;
		}
		if (r == 0)
			break ;
	}
	if (ft_strchr(map, 'C') > -1 || ft_strchr(map, 'E') > -1)
		return (free(map), 0);
	return (free(map), 1);
}

static int	checker_3(char *map, t_ints	vars)
{
	vars.i = (vars.x + 1) * (vars.y - 1);
	while (map[vars.i])
		if (map[vars.i++] != '1')
			return (free(map), 0);
	if (vars.i - (vars.x + 1) * (vars.y - 1) != vars.x)
		return (free(map), 0);
	vars.i = vars.x + 1;
	while (vars.i <= (vars.x + 1) * (vars.y - 1))
	{
		if (map[vars.i] != '1')
			return (free(map), 0);
		vars.i += (vars.x + 1);
	}
	vars.i = vars.x - 1;
	while (vars.i <= (vars.x + 1) * (vars.y) - 2)
	{
		if (map[vars.i] != '1')
			return (free(map), 0);
		vars.i += (vars.x + 1);
	}
	vars.p = ft_strchr(map, 'P');
	return (checker_4(map, vars));
}

static int	checker_2(char *map)
{
	t_ints	vars;

	vars.i = 0;
	vars.x = 0;
	vars.y = 1;
	while (map[vars.i])
	{
		if (map[vars.i] == '\n')
			vars.y++;
		if ((map[vars.i] != '1' && vars.y == 1)
			|| (map[vars.i] == '\n' && map[vars.i + 1] != '1'))
			return (free(map), 0);
		else if (vars.y == 1)
			vars.x++;
		vars.i++;
	}
	if (vars.x != vars.y)
		return (checker_3(map, vars));
	return (free(map), 0);
}

int	checker_1(char *map)
{
	t_ints	vars;

	vars.i = 0;
	vars.p = 0;
	vars.x = 0;
	vars.y = 0;
	while (map[vars.i])
	{
		if (vars.p > 1 || vars.y > 1)
			return (0);
		if (map[vars.i] == 'C')
			vars.x++;
		else if (map[vars.i] == 'P')
			vars.p++;
		else if (map[vars.i] == 'E')
			vars.y++;
		else if (map[vars.i] != '0' && map[vars.i] != '1'
			&& map[vars.i] != '\n' && map[vars.i] != 'X')
			return (0);
		vars.i++;
	}
	if (vars.x == 0)
		return (0);
	return (checker_2(map));
}

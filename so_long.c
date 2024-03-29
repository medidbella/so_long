/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:04:33 by midbella          #+#    #+#             */
/*   Updated: 2024/03/12 16:32:53 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	format_check(char *map)
{
	char	*format;
	int		i;
	int		j;

	format = ".ber";
	i = 0;
	j = 3;
	while (map[i])
		i++;
	i--;
	while (j >= 0)
		if (map[i--] != format[j--])
			return (0);
	return (1);
}

static void	starter(char *map, t_data *data)
{
	data->moves = 0;
	data->map = map;
	data->lc_frame = ft_strdup("textures/5_c.xpm");
	while (data->map[data->w_x])
	{
		if (data->map[data->w_x] == '1' && data->p_y == 1)
			data->p_x++;
		else if (data->map[data->w_x] == '\n')
			data->p_y++;
		data->w_x++;
	}
	data->w_x = data->p_x * 60;
	data->w_y = data->p_y * 60;
	data->p_x = 0;
	data->win = mlx_new_window(data->mlx_ptr, data->w_x, data->w_y, "so_long");
	if (!data->win)
		mlx_failed(data, NULL);
	put_space(data);
	put_etc(data, 0);
	mlx_key_hook(data->win, key_handler, data);
	mlx_hook(data->win, 17, 0, x_pressed, data);
	mlx_loop_hook(data->mlx_ptr, collectible, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*map;

	if (ac > 2)
		return (write(2, "Error\nonly one argument is allowed\n", 35), 1);
	else if (ac < 2)
		return (write(2, "Error\ninsert the map name\n", 26), 1);
	if (!format_check(av[1]))
		return (write(2, "Error\nplease inter a map in format *.ber\n", 41), 1);
	map = scaner(av[1]);
	if (!map)
		return (write(2, "Error\nfile not found or empty\n", 30), 1);
	if (!checker_1(map))
		return (write(2, "Error\ninvalid map\n", 18), 1);
	data.mlx_ptr = mlx_init();
	data.win = NULL;
	if (!data.mlx_ptr)
		mlx_failed(&data, NULL);
	data.p_y = 1;
	data.p_x = 0;
	data.w_x = 0;
	starter(scaner(av[1]), &data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:04:33 by midbella          #+#    #+#             */
/*   Updated: 2024/02/24 20:02:15 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	starter(char *map, t_data *data)
{
	data->p_y = 1;
	data->p_x = 0;
	data->w_x = 0;
	data->moves = 0;
	data->map = map;
	data->mlx_ptr = mlx_init();
	data->lc_frame = ft_strdup("images/5_c.xpm");
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
	put_space(data);
	put_etc(data, 0);
	mlx_key_hook(data->win, key_handler, data);
	mlx_loop_hook(data->mlx_ptr, collectible, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*tmp;
	char	*map;

	if (ac != 2)
		return (write(2, "Error\nonly one argument is allowed", 35), 1);
	tmp = scaner(av[1]);
	map = ft_strdup(tmp);
	if (!tmp)
		return (write(2, "Error\nfile not found", 20), 1);
	if (!checker_1(tmp))
		return (write(2, "Error\ninvald map", 17), 1);
	starter(map, &data);
}

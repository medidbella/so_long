/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:01:53 by midbella          #+#    #+#             */
/*   Updated: 2024/03/12 16:45:04 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
	
void	fill_scren(int color, t_data *data)
{
	t_ints	vars;
	void	*img;

	vars.x = 0;
	while (vars.x <= data->w_x)
	{
		vars.y = 0;
		while (vars.y <= data->w_y)
			mlx_pixel_put(data->mlx_ptr, data->win, vars.x, vars.y++, color);
		vars.x++;
	}
	if (color == 0xff0000)
		img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/game_over.xpm", &vars.p, &vars.i);
	else
		img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/you_won.xpm", &vars.p, &vars.i);
	mlx_failed(data, img);
	mlx_put_image_to_window(data->mlx_ptr, data->win,
		img, data->w_x / 2 - (vars.p / 2), data->w_y / 2 - (vars.i / 2));
	vars.x = 100;
	while (vars.x-- > 0)
		mlx_do_sync(data->mlx_ptr);
}

void	images_checker(t_data	*data, void *img[5])
{
	int	i;

	i = 0;
	while (i <= 3)
		mlx_failed(data, img[i++]);
}

int	x_pressed(t_data *data)
{
	finish_game(data, -1, 0);
	return (0);
}

void	mlx_failed(t_data *data, void *img)
{
	if (img)
		return ;
	if (data->win)
	{
		mlx_clear_window(data->mlx_ptr, data->win);
		mlx_destroy_window(data->mlx_ptr, data->win);
	}
	free(data->map);
	free(data->lc_frame);
	write(2, "Error\nprogramm failed\n", 22);
	exit(0);
}

void	finish_game(t_data *data, int state, char c)
{
	if (state == -1)
		write(1, "YOU EXITED THE GAME\n", 20);
	else if (c == 'E' && ft_strchr(data->map, 'C') == -1)
	{
		write(1, "YOU HAVE WON THE GAME", 21);
		fill_scren(0xffffff, data);
	}
	else if (c == 'X')
	{
		write(1, "YOU HAVE BEEN KILLED BY AN ENEMY\n", 33);
		fill_scren(0xff0000, data);
	}
	else
		return ;
	mlx_clear_window(data->mlx_ptr, data->win);
	mlx_destroy_window(data->mlx_ptr, data->win);
	free(data->map);
	free(data->lc_frame);
	exit(0);
}

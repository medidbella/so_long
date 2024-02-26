/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:39:38 by midbella          #+#    #+#             */
/*   Updated: 2024/02/24 22:29:14 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	barrier_check(t_data *data, int key)
{
	int	index;
	int	line;
	int	colume;
	int	i;

	i = 0;
	index = 0;
	line = (data->p_y / 60);
	colume = (data->p_x / 60);
	while (data->map[i] != '\n')
		i++;
	if (key == RIGHT)
		index = ((line * i + colume) + line) + 1;
	else if (key == LEFT)
		index = ((line * i + colume) + line) - 1;
	else if (key == DOWN)
		index = (((line + 1) * i + colume) + (line + 1));
	else if (key == UP)
		index = (((line - 1) * i + colume) + (line - 1));
	if (data->map[index] == '1')
		return (0);
	else if (data->map[index] == 'C')
		data->map[index] = '0';
	finish_game(data, 1, data->map[index]);
	return (1);
}

int	key_handler(int key, t_data *data)
{
	if (key == ESC)
		finish_game(data, -1, 0);
	if (barrier_check(data, key))
		data->moves++;
	if (key == UP && barrier_check(data, key))
	{
		animation(data, ft_strdup("images/u_4.xpm"), key);
		data->lp_farme = "images/u_4.xpm";
	}
	else if (key == LEFT && barrier_check(data, key))
	{
		animation(data, ft_strdup("images/l_4.xpm"), key);
		data->lp_farme = "images/l_4.xpm";
	}
	else if (key == RIGHT && barrier_check(data, key))
	{
		animation(data, ft_strdup("images/r_4.xpm"), key);
		data->lp_farme = "images/r_4.xpm";
	}
	else if (key == DOWN && barrier_check(data, key))
	{
		animation(data, ft_strdup("images/d_4.xpm"), key);
		data->lp_farme = "images/d_4.xpm";
	}
	return (0);
}

void	animation(t_data *data, char *str, int key)
{
	int	c;
	int	nb;
	int	i;

	c = (60 / 4);
	if (key == UP || key == LEFT)
		c *= -1;
	i = 0;
	initializer(data, str);
	while (data->images[i])
	{
		if (key == RIGHT || key == LEFT)
			data->p_x += c ;
		else if (key == UP || key == DOWN)
			data->p_y += c;
		nb = WAIT;
		while (nb-- > 0)
			mlx_do_sync(data->mlx_ptr);
		mlx_clear_window(data->mlx_ptr, data->win);
		put_space(data);
		put_etc(data, 1);
		mlx_put_image_to_window(data->mlx_ptr, data->win,
			data->images[i++], data->p_x, data->p_y);
	}
	free(str);
}

void	initializer(t_data *data, char *str)
{
	static int	i;
	int			nb;
	int			g;
	int			width;
	int			height;

	nb = str[9] - 48;
	data->images[nb] = NULL;
	g = 0;
	img_destroyer(data, data->images, i, 0);
	while (--nb >= 0)
	{
		data->images[nb] = mlx_xpm_file_to_image(data->mlx_ptr,
				str, &width, &height);
		str[9]--;
		g++;
	}
	i = g;
}

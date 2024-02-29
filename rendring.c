/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:24:08 by midbella          #+#    #+#             */
/*   Updated: 2024/02/26 21:18:07 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	loop_hook_sync(t_data *data, int x, int y)
{
	int		width;
	int		height;
	void	*img;

	if (data->lc_frame[9] > '5')
		data->lc_frame[9] = '1';
	img = mlx_xpm_file_to_image(data->mlx_ptr, data->lc_frame, &width, &height);
	mlx_put_image_to_window(data->images, data->win, img, x, y);
	mlx_destroy_image(data->mlx_ptr, img);
	data->lc_frame[9]++;
}

void	img_destroyer(t_data *data, void *img[5], int nb, int ft)
{
	char	*str;
	char	*tmp;

	if (nb == 0)
		return ;
	nb--;
	while (nb >= 0)
	{
		mlx_destroy_image(data->mlx_ptr, img[nb]);
		nb--;
	}
	if (ft != 0)
	{
		tmp = ft_itoa(data->moves);
		str = ft_strjoin("movements = ", tmp);
		mlx_string_put(data->mlx_ptr, data->win,
			data->w_x - 180, 0, 0, str);
		free(tmp);
		free(str);
	}
}

void	etc_img_put(t_data *data, void *img[5], t_ints vars, int caller)
{
	while (data->map[vars.i])
	{
		if (ft_strchr("EX1", data->map[vars.i]) != -1)
			mlx_put_image_to_window(data->mlx_ptr, data->win,
				img[ft_strchr("EX1", data->map[vars.i])], vars.x, vars.y);
		else if (data->map[vars.i] == 'C' && caller == 1)
			loop_hook_sync(data, vars.x, vars.y);
		else if (data->map[vars.i] == 'P' && data->p_x == 0)
		{
			mlx_put_image_to_window(data->mlx_ptr,
				data->win, img[3], vars.x, vars.y);
			data->p_x = vars.x;
			data->p_y = vars.y;
			data->lp_farme = "textures/d_3.xpm";
		}
		else if (data->map[vars.i] == '\n')
		{
			vars.y += 60;
			vars.x = -60;
		}
		vars.i++;
		vars.x += 60;
	}
	img_destroyer(data, img, 4, 1);
}

void	put_etc(t_data *data, int caller)
{
	t_ints	vars;
	void	*img[5];
	int		width;
	int		hight;

	vars.x = 0;
	vars.y = 0;
	vars.i = 0;
	vars.p = 0;
	img[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/e_1.xpm", &width, &hight);
	img[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/e_2.xpm", &width, &hight);
	img[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/e_4.xpm", &width, &hight);
	img[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/e_3.xpm", &width, &hight);
	if (ft_strchr(data->map, 'C') == -1)
	{
		mlx_destroy_image(data->mlx_ptr, img[0]);
		img[0] = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/portal_1.xpm", &width, &hight);
	}
	etc_img_put(data, img, vars, caller);
}

void	put_space(t_data *data)
{
	int		x;
	int		y;
	int		width;
	int		hight;
	void	*img_0;

	img_0 = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/wood_pl.xpm", &width, &hight);
	x = 60;
	y = 60;
	width = 60;
	hight = 60;
	while (x + 60 <= (data->w_x - 60))
	{
		y = 60;
		while (y + 60 <= (data->w_y - 60))
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win, img_0, x, y);
			y += 60;
		}
		x += 60;
	}
	mlx_destroy_image(data->mlx_ptr, img_0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animatoins_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:12:58 by midbella          #+#    #+#             */
/*   Updated: 2024/03/12 16:33:33 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	last_frame_handle(t_data *data)
{
	int		width;
	int		height;
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx_ptr, data->lp_farme,
			&width, &height);
	mlx_failed(data, img);
	mlx_put_image_to_window(data->mlx_ptr, data->win,
		img, data->p_x, data->p_y);
	mlx_destroy_image(data->mlx_ptr, img);
}

void	*wich_frame(t_data *data)
{
	char		*str;
	void		*img;
	static int	calls;
	int			width;
	int			height;

	str = ft_strdup("textures/1_c.xpm");
	if (calls > 5 && calls <= 10)
		str[9] = '2';
	else if (calls > 10 && calls <= 15)
		str[9] = '3';
	else if (calls > 15 && calls <= 20)
		str[9] = '4';
	else if (calls > 25 && calls <= 30)
		str[9] = '5';
	calls++;
	if (calls == 30)
		calls = 0;
	free(data->lc_frame);
	data->lc_frame = ft_strdup(str);
	img = mlx_xpm_file_to_image(data->mlx_ptr, str,
			&width, &height);
	mlx_failed(data, img);
	return (free(str), img);
}

int	collectible(t_data	*data)
{
	t_ints	vars;
	void	*img;

	vars.x = 0;
	vars.y = 0;
	vars.i = 0;
	mlx_clear_window(data->mlx_ptr, data->win);
	put_space(data);
	put_etc(data, 0);
	last_frame_handle(data);
	img = wich_frame(data);
	while (data->map[vars.i])
	{
		if (data->map[vars.i] == 'C')
			mlx_put_image_to_window(data->mlx_ptr, data->win,
				img, vars.x, vars.y);
		else if (data->map[vars.i] == '\n')
		{
			vars.y += 60;
			vars.x = -60;
		}
		vars.i++;
		vars.x += 60;
	}
	return (mlx_destroy_image(data->mlx_ptr, img));
}

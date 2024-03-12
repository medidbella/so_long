/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:19:23 by midbella          #+#    #+#             */
/*   Updated: 2024/03/12 15:40:25 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define WAIT 4
# define ESC 53
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include <fcntl.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win;
	char	*map;
	void	*images[5];
	int		p_x;
	int		p_y;
	int		w_x;
	int		w_y;
	int		moves;
	char	*lc_frame;
	char	*lp_farme;
}	t_data;

typedef struct s_ints
{
	int	x;
	int	y;
	int	p;
	int	i;
}	t_ints;

char	*scaner(char *file);
char	*ft_itoa(int n);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		ft_strchr(char *str, char c);
int		checker_1(char *map);
int		barrier_check(t_data *data, int key);
int		key_handler(int key, t_data *data);
void	animation(t_data	*data, char *str, int key);
void	initializer(t_data *data, char *str);
void	put_etc(t_data *data, int caller);
void	put_space(t_data *data);
int		collectible(t_data	*data);
void	img_destroyer(t_data *data, void *img[5], int nb, int ft);
void	finish_game(t_data *data, int state, char c);
int		x_pressed(t_data	*data);
void	mlx_failed(t_data *data, void *img);
void	images_checker(t_data	*data, void *img[5]);
#endif
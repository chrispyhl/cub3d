/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:59:33 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/07 17:11:53 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	rotate_vec(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * cos(angle) + *y * cos(angle);
}

void	pan_direction(t_engine *eng, mlx_key_data_t key)
{
	double	speed;
	
	speed = 0.05;
	if (key.key == MLX_KEY_LEFT)
	{
		rotate_vec(&eng->dir_x, &eng->dir_y, -speed);
		rotate_vec(&eng->plane_x, &eng->plane_y, -speed);
	}
	else if (key.key == MLX_KEY_RIGHT)
	{
		rotate_vec(&eng->dir_x, &eng->dir_y, speed);
		rotate_vec(&eng->plane_x, &eng->plane_y, speed);
	}
	eng->dirty = 1;
}

static void	apply_move(t_engine *eng, double move_x, double move_y)
{
	int	next_x;
	int	next_y;
	
	next_x = (int)(eng->pos_x + move_x);
	next_y = (int)(eng->pos_y + move_y);
	if (eng->settings->map_info->map[(int)eng->pos_y][next_x] != '1')
		eng->pos_x += move_x;
	if (eng->settings->map_info->map[next_y][(int)eng->pos_x] != '1')
		eng->pos_y += move_y;
}

void	pan_view(t_engine *eng, mlx_key_data_t key)
{
	double	s;

	s = 0.1;
	if (key.key == MLX_KEY_W)
		apply_move(eng, eng->dir_x * s, eng->dir_y * s);
	if (key.key == MLX_KEY_S)
		apply_move(eng, -eng->dir_x * s, -eng->dir_y * s);
	if (key.key == MLX_KEY_A)
		apply_move(eng, eng->plane_x * -s, eng->plane_y * -s);
	if (key.key == MLX_KEY_D)
		apply_move(eng, eng->plane_x * s, eng->plane_y * s);
	eng->dirty = 1;
}

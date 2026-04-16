/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:59:33 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/14 15:23:01 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	is_walkable_tile(t_engine *eng, int x, int y)
{
	char	**map;

	map = eng->settings->map_info->map;
	if (y < 0 || y >= (int)eng->settings->map_info->y_height)
		return (0);
	if (x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '1' || map[y][x] == ' ')
		return (0);
	return (1);
}

static void	rotate_vec(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	pan_direction(t_engine *eng, mlx_key_data_t key)
{
	double	speed;

	speed = 0.03;
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
	int	cur_x;
	int	cur_y;

	cur_x = (int)eng->pos_x;
	cur_y = (int)eng->pos_y;
	if (is_walkable_tile(eng, (int)(eng->pos_x + move_x),
		(int)(eng->pos_y + move_y)))
	{
		eng->pos_x += move_x;
		eng->pos_y += move_y;
	}
}

void	pan_view(t_engine *eng, mlx_key_data_t key)
{
	double	s;

	s = 0.03;
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

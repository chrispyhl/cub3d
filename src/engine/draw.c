/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:21:56 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/10 11:55:07 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	prepare_ray(t_engine *eng, int x)
{
	double	camera_x;

	camera_x = 2 * (double)x / (double)WIDTH - 1;
	eng->r_dir_x = eng->dir_x + eng->plane_x * camera_x;
	eng->r_dir_y = eng->dir_y + eng->plane_y * camera_x;
	eng->mapX = (int)eng->pos_x;
	eng->mapY = (int)eng->pos_y;
	if (eng->r_dir_x == 0)
		eng->deltaDistX = 1e30;
	else
		eng->deltaDistX = fabs(1 / eng->r_dir_x);
	if (eng->r_dir_y == 0)
		eng->deltaDistY = 1e30;
	else
		eng->deltaDistY = fabs(1 / eng->r_dir_y);
}

static void	set_dda_step(t_engine *eng)
{
	if (eng->r_dir_x < 0)
	{
		eng->stepX = -1;
		eng->sideDistX = (eng->pos_x - eng->mapX) * eng->deltaDistX;
	}
	else
	{
		eng->stepX = 1;
		eng->sideDistX = (eng->mapX + 1.0 - eng->pos_x) * eng->deltaDistX;
	}
	if (eng->r_dir_y < 0)
	{
		eng->stepY = -1;
		eng->sideDistY = (eng->pos_y - eng->mapY) * eng->deltaDistY;
	}
	else
	{
		eng->stepY = 1;
		eng->sideDistY = (eng->mapY + 1.0 - eng->pos_y) * eng->deltaDistY;
	}
}

static int	perform_dda(t_engine *eng)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (eng->sideDistX < eng->sideDistY)
		{
			eng->sideDistX += eng->deltaDistX;
			eng->mapX += (int)eng->stepX;
			side = 0;
		}
		else
		{
			eng->sideDistY += eng->deltaDistY;
			eng->mapY += (int)eng->stepY;
			side = 1;
		}
		if (eng->settings->map_info->map[eng->mapY][eng->mapX] == '1')
			hit = 1;
	}
	return (side);
}

void	draw_game(void *param)
{
	t_engine	*eng;
	int			x;
	int			side;
	double		r_dir[2];
	double		perp_dist;

	eng = (t_engine *)param;
	x = 0;
	while (x < WIDTH)
	{
		prepare_ray(eng, x);
		set_dda_step(eng);
		side = perform_dda(eng);
		if (side == 0)
			perp_dist = (eng->sideDistX - eng->deltaDistX);
		else
			perp_dist = (eng->sideDistY - eng->deltaDistY);
		render_column(eng, x, side, perp_dist);
		x++;
	}
}

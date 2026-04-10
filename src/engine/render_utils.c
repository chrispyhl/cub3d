/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:54:41 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/10 12:02:43 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	get_wall_color(t_engine *eng, int side)
{
	if (side == 0)
	{
		if (eng->stepX > 0)
			return (0xFF0000FF);
		return (0x00FF00FF);
	}
	else
	{
		if (eng->stepY > 0)
			return (0x0000FFFF);
		return (0xFFFF00FF);
	}
}

static void	draw_vertical_line(t_engine *eng, int x, int draw[2], int color)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < draw[0])
			mlx_put_pixel(eng->img, x, y, eng->settings->color_info->ceil_color);
		else if (y >= draw[0] && y <= draw[1])
			mlx_put_pixel(eng->img, x, y, color);
		else
			mlx_put_pixel(eng->img, x, y, eng->settings->color_info->floor_color);
	}
}

void	render_column(t_engine *eng, int x, int side, double perp_dist)
{
	int	line_h;
	int	draw[2];
	int	color;

	line_h = (int)(HEIGHT / perp_dist);
	draw[0] = -line_h / 2 + HEIGHT / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = line_h / 2 + HEIGHT / 2;
	if (draw[1] >= HEIGHT)
		draw[1] = HEIGHT - 1;
	color = get_wall_color(eng, side);
	draw_vertical_line(eng, x, draw, color);
}

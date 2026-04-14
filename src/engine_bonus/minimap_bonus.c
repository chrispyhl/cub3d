/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:07:00 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/14 15:41:21 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_bonus.h"

static void	draw_player_icon(t_engine *eng)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = (int)(eng->pos_x * 10) - 2;
	py = (int)(eng->pos_y * 10) - 2;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (px + x >= 0 && px + x < 200 && py + y >= 0 && py + y < 200)
				mlx_put_pixel(eng->minimap_img, px + x, py + y, 0xFF000088);
			x++;
		}
		y++;
	}
}

static void	draw_map(t_engine *eng, int *x, int *y)
{
	eng->map_x = *x / 10;
	eng->map_y = *y / 10;
	if (eng->map_y < (int)eng->settings->map_info->y_height
		&& eng->map_x
		< (int)ft_strlen(eng->settings->map_info->map[eng->map_y]))
	{
		if (eng->settings->map_info->map[eng->map_y][eng->map_x] == '1')
			mlx_put_pixel(eng->minimap_img, *x, *y, 0xFFFFFFFF);
		else
			mlx_put_pixel(eng->minimap_img, *x, *y, 0x00000088);
	}
	else
		mlx_put_pixel(eng->minimap_img, *x, *y, 0x00000000);
}

void	draw_minimap(t_engine *eng)
{
	int	y;
	int	x;

	y = 0;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			draw_map(eng, &x, &y);
			x++;
		}
		y++;
	}
	draw_player_icon(eng);
}

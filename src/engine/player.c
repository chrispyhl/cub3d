/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:35:53 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/16 15:42:35 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	set_view_angle(t_engine *engine)
{
	char	dir;

	dir = engine->settings->player_info->dir;
	if (dir == 'N')
	{
		engine->dir_x = 0;
		engine->dir_y = -1;
	}
	if (dir == 'S')
	{
		engine->dir_x = 0;
		engine->dir_y = 1;
	}
	if (dir == 'E')
	{
		engine->dir_x = 1;
		engine->dir_y = 0;
	}
	if (dir == 'W')
	{
		engine->dir_x = -1;
		engine->dir_y = 0;
	}
	engine->plane_x = -engine->dir_y * 0.66;
	engine->plane_y = engine->dir_x * 0.66;
}

void	init_player(t_engine *engine)
{
	engine->pos_x = engine->settings->player_info->player_x;
	engine->pos_y = engine->settings->player_info->player_y;
	set_view_angle(engine);
}

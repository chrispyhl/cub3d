/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:31:38 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/07 17:12:34 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	on_key_press(mlx_key_data_t k, void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (k.key == MLX_KEY_ESCAPE && (k.action == MLX_PRESS))
	{
		mlx_close_window(engine->mlx);
		free_settings(engine->settings);
	}
	if (k.action != MLX_PRESS && k.action != MLX_REPEAT)
		return ;
	pan_direction(engine, k);
	pan_view(engine, k);
}

void	redraw(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (engine->dirty)
	{
		draw_game(engine);
		engine->dirty = 0;
	}
}
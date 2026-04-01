/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:31:38 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/01 15:33:20 by cpohl            ###   ########.fr       */
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
	if (k.key == MLX_KEY_LEFT && (k.action == MLX_PRESS) 
		|| k.key == MLX_KEY_RIGHT && (k.action == MLX_PRESS))
		pan_direction(engine, k.key);
	if (k.key == MLX_KEY_W || k.key == MLX_KEY_S || k.key == MLX_KEY_A
		|| k.key == MLX_KEY_D)
		pan_view(engine, k.key);
	// else if (k.key == MLX_KEY_TAB)
	// 	show_minimap(engine);
	else
		return ;
	engine->dirty = 1;
}

void	redraw(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (engine->dirty)
	{
		engine->draw_game(engine);
		engine->dirty = 0;
	}
}
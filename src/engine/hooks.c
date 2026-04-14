/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:31:38 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/14 15:21:17 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static mlx_key_data_t	make_key_event(int key)
{
	mlx_key_data_t	k;

	k.key = key;
	k.action = MLX_PRESS;
	k.os_key = 0;
	k.modifier = 0;
	return (k);
}

static void	poll_rotation_keys(t_engine *engine)
{
	if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT))
		pan_direction(engine, make_key_event(MLX_KEY_LEFT));
	if (mlx_is_key_down(engine->mlx, MLX_KEY_RIGHT))
		pan_direction(engine, make_key_event(MLX_KEY_RIGHT));
}

static void	poll_move_keys(t_engine *engine)
{
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
		pan_view(engine, make_key_event(MLX_KEY_W));
	if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
		pan_view(engine, make_key_event(MLX_KEY_S));
	if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
		pan_view(engine, make_key_event(MLX_KEY_A));
	if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
		pan_view(engine, make_key_event(MLX_KEY_D));
}

void	on_key_press(mlx_key_data_t k, void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (k.key == MLX_KEY_ESCAPE && (k.action == MLX_PRESS))
	{
		mlx_close_window(engine->mlx);
		return ;
	}
}

void	redraw(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	poll_rotation_keys(engine);
	poll_move_keys(engine);
	if (engine->dirty)
	{
		draw_game(engine);
		engine->dirty = 0;
	}
}

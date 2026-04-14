/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:46:39 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/14 15:19:22 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_bonus.h"

static int	init_mlx_scene(t_engine *engine)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	engine->mlx = mlx_init(WIDTH, HEIGHT, "chr3d", false);
	if (!engine->mlx)
		return (1);
	engine->img = mlx_new_image(engine->mlx, WIDTH, HEIGHT);
	if (!engine->img)
		return (mlx_terminate(engine->mlx), 1);
	if (mlx_image_to_window(engine->mlx, engine->img, 0, 0) < 0)
	{
		mlx_delete_image(engine->mlx, engine->img);
		return (mlx_terminate(engine->mlx), 1);
	}
	engine->minimap_img = mlx_new_image(engine->mlx, 200, 200);
	if (!engine->minimap_img)
		return (mlx_terminate(engine->mlx), 1);
	mlx_image_to_window(engine->mlx, engine->minimap_img, WIDTH - 210, 10);
	engine->minimap_img->enabled = false;
	if (!load_tex(engine))
	{
		mlx_delete_image(engine->mlx, engine->img);
		return (mlx_terminate(engine->mlx), 1);
	}
	return (0);
}

void	init_hooks(t_engine *engine)
{
	mlx_key_hook(engine->mlx, on_key_press, engine);
	mlx_loop_hook(engine->mlx, redraw, engine);
}

int	run_mlx(t_engine *engine)
{
	if (init_mlx_scene(engine))
		return (1);
	draw_game(engine);
	engine->dirty = 0;
	init_hooks(engine);
	mlx_loop(engine->mlx);
	free_tex(engine);
	mlx_terminate(engine->mlx);
	return (0);
}

t_engine	*init_engine(t_settings *settings)
{
	t_engine	*engine;

	engine = ft_calloc(1, sizeof(t_engine));
	if (!engine)
		return (NULL);
	engine->settings = settings;
	return (engine);
}

int	start_engine(t_settings *settings)
{
	t_engine	*engine;
	int			status;

	status = 0;
	engine = init_engine(settings);
	if (!engine)
		return (1);
	init_player(engine);
	status = run_mlx(engine);
	free(engine);
	return (status);
}

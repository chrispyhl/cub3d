/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:46:39 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/07 16:25:05 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	init_hooks(t_engine *engine)
{
	mlx_key_hook(engine->mlx, on_key_press, engine);
	mlx_loop_hook(engine->mlx, redraw, engine);
}

int	run_mlx(t_engine *engine)
{
	mlx_set_settings(MLX_MAXIMIZED, false);
	engine->mlx = mlx_init(WIDTH, HEIGHT, "chr3d", false);
	if (!engine->mlx)
		return (1); // error
	engine->img = mlx_new_image(engine->mlx, WIDTH, HEIGHT);
	if (!engine->img)
	{
		mlx_terminate(engine->mlx);
		return (1); // error
	}
	if (mlx_image_to_window(engine->mlx, engine->img, 0, 0) < 0)
	{
		mlx_delete_image(engine->mlx, engine->img);
		mlx_terminate(engine->mlx);
		return (1); // error
	}
	init_hooks(engine);
	mlx_loop(engine->mlx);
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

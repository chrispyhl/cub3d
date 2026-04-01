/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:39:24 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/01 15:44:05 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "main.h"
# include <MLX42/MLX42.h>

typedef struct s_engine
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_settings	*settings;
	int			dirty;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_engine;

// Functions
int		start_engine(t_engine *engine);

// void	draw_game();

// MLX Stuff
int		run_mlx(t_engine *engine);
void	init_hooks(t_engine *engine);

#endif

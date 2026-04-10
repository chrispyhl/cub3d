/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:39:24 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/10 12:07:47 by cpohl            ###   ########.fr       */
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
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		stepX;
	double		stepY;
	double		r_dir_x;
	double		r_dir_y;
	int			mapX;
	int			mapY;
}				t_engine;

// Functions
int			start_engine(t_settings *settings);
t_engine	*init_engine(t_settings *settings);

void		init_player(t_engine *engine);
void		set_view_angle(t_engine *engine);

void		draw_game(void *param);
void		render_column(t_engine *eng, int x, int side, double perp_dist);

void		pan_direction(t_engine *eng, mlx_key_data_t key);
void		pan_view(t_engine *eng, mlx_key_data_t key);

// MLX Stuff
int			run_mlx(t_engine *engine);
void		init_hooks(t_engine *engine);

void		on_key_press(mlx_key_data_t k, void *param);
void		redraw(void *param);

#endif

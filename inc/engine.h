/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:39:24 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/14 15:14:01 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "main.h"

# ifndef WIDTH
#  define WIDTH 800
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif

typedef struct s_engine
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap_img;
	mlx_texture_t	*no_tex_img;
	mlx_texture_t	*so_tex_img;
	mlx_texture_t	*we_tex_img;
	mlx_texture_t	*ea_tex_img;
	t_settings		*settings;
	int				dirty;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			step_x;
	double			step_y;
	double			r_dir_x;
	double			r_dir_y;
	int				map_x;
	int				map_y;
	int				line_h;
	int				draw_start;
	int				draw_end;
}					t_engine;

// Functions
int					start_engine(t_settings *settings);
t_engine			*init_engine(t_settings *settings);

void				init_player(t_engine *engine);
void				set_view_angle(t_engine *engine);

int					load_tex(t_engine *eng);
void				free_tex(t_engine *eng);

void				draw_game(void *param);
void				render_column(t_engine *eng, int x, int side,
						double perp_dist);

void				pan_direction(t_engine *eng, mlx_key_data_t key);
void				pan_view(t_engine *eng, mlx_key_data_t key);

// MLX Stuff
int					run_mlx(t_engine *engine);
void				init_hooks(t_engine *engine);

void				on_key_press(mlx_key_data_t k, void *param);
void				redraw(void *param);

#endif

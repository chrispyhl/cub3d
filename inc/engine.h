/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:39:24 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/16 17:35:47 by cpohl            ###   ########.fr       */
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
	mlx_t			*mlx; // mlx context
	mlx_image_t		*img; // Hauptbild
	mlx_image_t		*minimap_img; // Minimap Bild
	mlx_texture_t	*no_tex_img; // Texture Nord
	mlx_texture_t	*so_tex_img; // Texture Süd
	mlx_texture_t	*we_tex_img; // Texture West
	mlx_texture_t	*ea_tex_img; // Texture Ost
	t_settings		*settings; // Parser dinge
	int				dirty; // Für wann redraw
	double			pos_x; // Spielerposition X.x
	double			pos_y; // Spielerposition Y.y
	double			dir_x; // Blickrichtungs Vektor x = 1 = nach rechts schauen
	double			dir_y; // Blickrichtungs Vektor y = 1 = nach oben schauen
	double			plane_x; // Orientierung im Raum. (Wo schaue ich gerade hin)
	double			plane_y; // Vorstellbar wie stoßstange. Vertikale linie vor dem Auge
	double			side_dist_x; // tatsächliche Distanz zu nächsten Gitterline X
	double			side_dist_y; // tatsächliche Distanz zu nächsten Gitterline Y
	double			delta_dist_x; // Horizontale Distanz zur nächsten Gitterlinie X
	double			delta_dist_y; // Vertikale Distanz zur nächsten Gitterlinie Y
	double			step_x; // Sprungrichtung für map[x, y]
	double			step_y; // Sprungrichtung für map[x, y]
	double			r_dir_x; // ray strahl der in bestimmtem Winkel durch map fliegt
	double			r_dir_y; // ''
	int				map_x; // Aktuelle Gitterkoordinate (3)
	int				map_y; // Aktuelle Gitterkoordinate (2) == map [3 | 2]
	int				line_h; // Höhe der Wand die gezeichnet werden soll
	int				draw_start; // Start zu pixeln 
	int				draw_end; // Ende zu pixeln
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

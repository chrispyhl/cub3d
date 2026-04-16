/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:21:56 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/16 17:48:32 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	draw_background(t_engine *eng)
{
	int			x;
	int			y;
	uint32_t	ceil_col;
	uint32_t	floor_col;

	ceil_col = ((uint32_t)eng->settings->color_info->ceil_color << 8) | 0xFF;
	floor_col = ((uint32_t)eng->settings->color_info->floor_color << 8) | 0xFF;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(eng->img, x, y, ceil_col);
			else
				mlx_put_pixel(eng->img, x, y, floor_col);
			x++;
		}
		y++;
	}
}

static void	prepare_ray(t_engine *eng, int x) // Hier berechnen wir camera_x und r_dir (Wohin schauen wir)
{
	double	camera_x;

	camera_x = 2 * (double)x / (double)WIDTH - 1; // Where exactly am I watching right now?
	eng->r_dir_x = eng->dir_x + eng->plane_x * camera_x; // präziser Punkt wohin ich gerade schaue 
	eng->r_dir_y = eng->dir_y + eng->plane_y * camera_x;
	eng->map_x = (int)eng->pos_x; // aktuelle position gerundet
	eng->map_y = (int)eng->pos_y;
	if (eng->r_dir_x == 0) // wenn genau nach rechts dann gegen undendlich
		eng->delta_dist_x = 1e30;
	else
		eng->delta_dist_x = fabs(1 / eng->r_dir_x);
	if (eng->r_dir_y == 0)
		eng->delta_dist_y = 1e30; // wenn genau nach oben dann gegen unendlich
	else
		eng->delta_dist_y = fabs(1 / eng->r_dir_y);
}

static void	set_dda_step(t_engine *eng) // Berechnung der side dist
{
	if (eng->r_dir_x < 0)
	{
		eng->step_x = -1; // strahl nach links
		eng->side_dist_x = (eng->pos_x - eng->map_x) * eng->delta_dist_x;	// Kalkulation für Distanz zu seite
	}																		// Spieler pos - map pos * winkel des strahls
	else
	{
		eng->step_x = 1; // strahl nach rechts
		eng->side_dist_x = (eng->map_x + 1.0 - eng->pos_x) * eng->delta_dist_x;
	}
	if (eng->r_dir_y < 0)
	{
		eng->step_y = -1; // strahl nach unten
		eng->side_dist_y = (eng->pos_y - eng->map_y) * eng->delta_dist_y;
	}
	else
	{
		eng->step_y = 1; // strahl nach oben
		eng->side_dist_y = (eng->map_y + 1.0 - eng->pos_y) * eng->delta_dist_y;
	}
}

static int	perform_dda(t_engine *eng) // Anwendung der Werte
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (eng->side_dist_x < eng->side_dist_y) // Wenn x schneller als y ist
		{
			eng->side_dist_x += eng->delta_dist_x; // "Lauf" die Distanz zu nächster Gitterlinie
			eng->map_x += (int)eng->step_x; // Erhöhe Map Koordinate um 1
			side = 0;
		}
		else
		{
			eng->side_dist_y += eng->delta_dist_y;
			eng->map_y += (int)eng->step_y;
			side = 1;
		}
		if (eng->settings->map_info->map[eng->map_y][eng->map_x] == '1') // Wenn Wand getroffen stop
			hit = 1;
	}
	return (side);
}

void	draw_game(void *param)
{
	t_engine	*eng;
	int			x;
	int			side;
	double		perp_dist;

	eng = (t_engine *)param;
	draw_background(eng);
	x = 0;
	while (x < WIDTH)
	{
		prepare_ray(eng, x);
		set_dda_step(eng);
		side = perform_dda(eng);
		if (side == 0) // Wenn Vertikale Wand
			perp_dist = (eng->side_dist_x - eng->delta_dist_x); // Einmal delta dist abziehen um Fischauge Effekt zu vermeiden
		else
			perp_dist = (eng->side_dist_y - eng->delta_dist_y);
		render_column(eng, x, side, perp_dist); // rendern
		x++;
	}
}

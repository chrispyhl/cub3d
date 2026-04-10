/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:54:41 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/10 18:47:02 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static mlx_texture_t	*get_wall_texture(t_engine *eng, int side)
{
	if (side == 0)
	{
		if (eng->stepX > 0)
			return (eng->ea_tex_img);
		return (eng->we_tex_img);
	}
	if (eng->stepY > 0)
		return (eng->so_tex_img);
	return (eng->no_tex_img);
}

static uint32_t	get_texel_color(mlx_texture_t *tex, int tex_x, double tex_pos)
{
	int			idx;
	int			tex_y;
	uint8_t		*p;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)tex->height)
		tex_y = (int)tex->height - 1;
	idx = (tex_y * tex->width + tex_x) * 4;
	p = &tex->pixels[idx];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static int	get_tex_x(t_engine *eng, mlx_texture_t *tex, int side,
		double perp_dist)
{
	int		tex_x;
	double	wall_x;

	if (side == 0)
		wall_x = eng->pos_y + perp_dist * eng->r_dir_y;
	else
		wall_x = eng->pos_x + perp_dist * eng->r_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = (int)tex->width - 1;
	if ((side == 0 && eng->r_dir_x > 0) || (side == 1 && eng->r_dir_y < 0))
		tex_x = (int)tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_vertical_line(t_engine *eng, int x, int side, double perp_dist)
{
	int			y;
	int			tex_x;
	double		step;
	double		tex_pos;

	if (!get_wall_texture(eng, side) || get_wall_texture(eng, side)->width == 0
		|| get_wall_texture(eng, side)->height == 0)
		return ;
	tex_x = get_tex_x(eng, get_wall_texture(eng, side), side, perp_dist);
	step = (double)get_wall_texture(eng, side)->height / (double)eng->line_h;
	tex_pos = (eng->draw_start - HEIGHT / 2 + eng->line_h / 2) * step;
	y = eng->draw_start;
	while (y <= eng->draw_end)
	{
		mlx_put_pixel(eng->img, x, y++, get_texel_color(get_wall_texture(eng,
					side), tex_x, tex_pos));
		tex_pos += step;
	}
}

void	render_column(t_engine *eng, int x, int side, double perp_dist)
{
	if (perp_dist < 0.0001)
		perp_dist = 0.0001;
	eng->line_h = (int)(HEIGHT / perp_dist);
	eng->draw_start = -eng->line_h / 2 + HEIGHT / 2;
	if (eng->draw_start < 0)
		eng->draw_start = 0;
	eng->draw_end = eng->line_h / 2 + HEIGHT / 2;
	if (eng->draw_end >= HEIGHT)
		eng->draw_end = HEIGHT - 1;
	draw_vertical_line(eng, x, side, perp_dist);
}

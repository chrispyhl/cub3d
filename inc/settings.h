/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:07:42 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 15:47:51 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

typedef struct s_tex_info
{
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			*ea_tex;
}					t_tex_info;

typedef struct s_color_info
{
	int				floor_color;
	int				ceil_color;
}					t_color_info;

typedef struct s_map_info
{
	char			**map;
	size_t			x_width;
	size_t			y_height;
	int				spill_flag;
}					t_map_info;

typedef struct s_player_info
{
	double			player_x;
	double			player_y;
	char			dir;
}					t_player_info;

typedef struct s_settings
{
	char			*cub_path;
	t_tex_info		*tex_info;
	t_color_info	*color_info;
	t_map_info		*map_info;
	t_player_info	*player_info;

}					t_settings;

#endif

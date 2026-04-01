/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_create_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:05:25 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 15:48:10 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: shorten paths when Makefile is ready
#include "../../inc/parser.h"

static void	populate_settings(t_settings *settings)
{
	settings->tex_info->no_tex = NULL;
	settings->tex_info->so_tex = NULL;
	settings->tex_info->we_tex = NULL;
	settings->tex_info->ea_tex = NULL;
	settings->color_info->floor_color = -1;
	settings->color_info->ceil_color = -1;
	settings->map_info->map = NULL;
	settings->map_info->x_width = 0;
	settings->map_info->y_height = 0;
	settings->map_info->spill_flag = 0;
	settings->player_info->dir = 'x';
	settings->player_info->player_x = 0;
	settings->player_info->player_y = 0;
}

static t_settings	*create_settings_var(char *arg)
{
	t_settings		*settings;
	t_tex_info		*tex_info;
	t_color_info	*color_info;
	t_map_info		*map_info;
	t_player_info	*player_info;

	settings = ft_calloc(1, sizeof(t_settings));
	if (!settings)
		return (NULL);
	tex_info = ft_calloc(1, sizeof(t_tex_info));
	settings->tex_info = tex_info;
	color_info = ft_calloc(1, sizeof(t_color_info));
	settings->color_info = color_info;
	map_info = ft_calloc(1, sizeof(t_map_info));
	settings->map_info = map_info;
	player_info = ft_calloc(1, sizeof(t_player_info));
	settings->player_info = player_info;
	if (!tex_info || !color_info || !map_info || handle_cub_path(arg,
			settings) != 1)
		return (NULL);
	populate_settings(settings);
	return (settings);
}

t_settings	*create_settings(char *arg)
{
	t_settings	*settings;

	settings = create_settings_var(arg);
	if (!settings)
	{
		free_settings(settings);
		return (NULL);
	}
	if (parse_cub(settings) != 1)
	{
		free_settings(settings);
		return (NULL);
	}
	if (verify_tex_info(settings) != 1 || verify_color_info(settings) != 1
		|| verify_map_info(settings) != 1)
	{
		free_settings(settings);
		return (NULL);
	}
	return (settings);
}

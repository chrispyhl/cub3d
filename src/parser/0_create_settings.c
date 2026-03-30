/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_create_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:05:25 by craabe            #+#    #+#             */
/*   Updated: 2026/03/30 20:28:14 by gries            ###   ########.fr       */
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
}

static t_settings	*create_settings_var(char *arg)
{
	t_settings		*settings;
	t_tex_info		*tex_info;
	t_color_info	*color_info;
	t_map_info		*map_info;

	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (NULL);
	tex_info = malloc(sizeof(t_tex_info));
	settings->tex_info = tex_info;
	color_info = malloc(sizeof(t_color_info));
	settings->color_info = color_info;
	map_info = malloc(sizeof(t_map_info));
	settings->map_info = map_info;
	if (!tex_info || !color_info || !map_info || handle_cub_path(arg,
			settings) != 1)
	{
		free_settings(settings);
		return (NULL);
	}
	populate_settings(settings);
	return (settings);
}

static int	parse_cub(t_settings *settings)
{
	int		fd;
	char	*raw_line;
	char	*line;
	int		valid_flag;

	fd = open(settings->cub_path, O_RDONLY);
	raw_line = get_next_line(fd);
	valid_flag = 1;
	while (raw_line)
	{
		line = sanitize_line(raw_line);
		free(raw_line);
		if (valid_flag == 1 && (ft_strncmp(line, "NO ", 3) == 0
				|| ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ",
					3) == 0 || ft_strncmp(line, "EA ", 3) == 0))
			valid_flag = add_tex_info(settings, line);
		else if (valid_flag == 1 && (ft_strncmp(line, "F ", 2) == 0
				|| ft_strncmp(line, "C ", 2) == 0))
			valid_flag = add_color_info(settings, line);
		free(line);
		raw_line = get_next_line(fd);
	}
	close(fd);
	return (valid_flag);
}

static int	verify_settings(t_settings *settings)
{
	if (verify_tex_info(settings) != 1 || verify_color_info(settings) != 1)
		return (0);
	return (1);
}

t_settings	*create_settings(char *arg)
{
	t_settings	*settings;

	settings = create_settings_var(arg);
	if (!settings)
		return (NULL);
	if (parse_cub(settings) != 1)
	{
		free_settings(settings);
		return (NULL);
	}
	if (verify_settings(settings) != 1)
	{
		free_settings(settings);
		return (NULL);
	}
	return (settings);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_create_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:05:25 by craabe            #+#    #+#             */
/*   Updated: 2026/03/31 11:04:19 by gries            ###   ########.fr       */
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

	settings = ft_calloc(1, sizeof(t_settings));
	if (!settings)
		return (NULL);
	tex_info = ft_calloc(1, sizeof(t_tex_info));
	settings->tex_info = tex_info;
	color_info = ft_calloc(1, sizeof(t_color_info));
	settings->color_info = color_info;
	map_info = ft_calloc(1, sizeof(t_map_info));
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

static void	process_line(t_settings *settings, t_map_list *map_list,
		char *raw_line, int *valid_flag)
{
	char	*line;

	line = sanitize_line(raw_line);
	if (*valid_flag == 1 && (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line,
				"SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0))
		*valid_flag = add_tex_info(settings, line);
	else if (*valid_flag == 1 && (ft_strncmp(line, "F ", 2) == 0
			|| ft_strncmp(line, "C ", 2) == 0))
		*valid_flag = add_color_info(settings, line);
	else if (*valid_flag == 1 && line[0] == '1')
		if (add_map_node(map_list, raw_line) == -1)
			*valid_flag = 0;
	free(raw_line);
	free(line);
}

static int	parse_cub(t_settings *settings)
{
	int			fd;
	char		*raw_line;
	int			valid_flag;
	t_map_list	*map_list;

	fd = open(settings->cub_path, O_RDONLY);
	raw_line = get_next_line(fd);
	valid_flag = 1;
	map_list = populate_map_list();
	while (raw_line)
	{
		process_line(settings, map_list, raw_line, &valid_flag);
		raw_line = get_next_line(fd);
	}
	close(fd);
	if (add_map_info(settings, map_list) != 1)
		valid_flag = 0;
	free_map_list(map_list);
	return (valid_flag);
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
	// TODO: add map verification function call
	if (verify_tex_info(settings) != 1 || verify_color_info(settings) != 1
		|| verify_map_info(settings) != 1)
	{
		free_settings(settings);
		return (NULL);
	}
	return (settings);
}

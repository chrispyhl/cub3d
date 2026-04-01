/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:56 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 10:47:57 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	handler_selector(t_cub_content content, t_settings *settings,
		t_map_list *map_list, char *line)
{
	if (content == TEXTURE)
	{
		if (map_list->size > 0)
		{
			ft_putstr_fd("ERROR: Texture path and map interfering.\n", 1);
			return (0);
		}
		return (add_tex_info(settings, line));
	}
	else if (content == COLOR)
	{
		if (map_list->size > 0)
		{
			ft_putstr_fd("ERROR: Color code and map interfering.\n", 1);
			return (0);
		}
		return (add_color_info(settings, line));
	}
	return (1);
}

static void	process_line(t_settings *settings, t_map_list *map_list,
		char *raw_line, int *valid_flag)
{
	char	*line;

	line = sanitize_line(raw_line);
	if (*valid_flag == 1 && (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line,
				"SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0))
		*valid_flag = handler_selector(TEXTURE, settings, map_list, line);
	else if (*valid_flag == 1 && (ft_strncmp(line, "F ", 2) == 0
			|| ft_strncmp(line, "C ", 2) == 0))
		*valid_flag = handler_selector(COLOR, settings, map_list, line);
	else if (*valid_flag == 1 && line[0] == '1')
		if (map_list->map_parsed == 1 || add_map_node(map_list, raw_line) != 1)
		{
			ft_putstr_fd("ERROR: Gap in map.\n", 1);
			*valid_flag = 0;
		}
	if (map_list->map_parsed == 0 && *valid_flag == 1 && map_list->size > 0
		&& line[0] != '1')
		map_list->map_parsed = 1;
	free(raw_line);
	free(line);
}

int	parse_cub(t_settings *settings)
{
	int fd;
	char *raw_line;
	int valid_flag;
	t_map_list *map_list;

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
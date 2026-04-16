/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_map_handling_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:00:19 by craabe            #+#    #+#             */
/*   Updated: 2026/04/16 17:33:27 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	find_min_indent(t_settings *settings)
{
	size_t	min_indent;
	size_t	spaces;
	char	**map;
	int		i;

	min_indent = SIZE_MAX;
	map = settings->map_info->map;
	i = 0;
	while (map[i])
	{
		spaces = 0;
		while (map[i][spaces] == ' ')
			spaces++;
		if (spaces < min_indent)
			min_indent = spaces;
		i++;
	}
	return (min_indent);
}

int	left_align_map(t_settings *settings)
{
	size_t	min_indent;
	int		i;
	char	**map;
	char	*aligned_line;

	min_indent = find_min_indent(settings);
	if (min_indent == 0)
		return (1);
	i = 0;
	map = settings->map_info->map;
	while (map[i])
	{
		aligned_line = ft_substr(map[i], (unsigned int)min_indent,
				ft_strlen(map[i]) - min_indent);
		if (!aligned_line)
			return (0);
		free(map[i]);
		map[i] = aligned_line;
		i++;
	}
	return (1);
}

static int	add_padded_line(t_settings *settings, size_t *i)
{
	char	*new_str;
	size_t	j;

	new_str = malloc(((settings->map_info->x_width) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	j = 0;
	while (settings->map_info->map[*i][j])
	{
		new_str[j] = settings->map_info->map[*i][j];
		j++;
	}
	while (j < settings->map_info->x_width)
	{
		new_str[j] = ' ';
		j++;
	}
	new_str[j] = '\0';
	free(settings->map_info->map[*i]);
	settings->map_info->map[*i] = new_str;
	return (1);
}

int	add_padding(t_settings *settings)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (settings->map_info->map[i])
	{
		j = ft_strlen(settings->map_info->map[i]);
		if (j < settings->map_info->x_width)
			if (add_padded_line(settings, &i) != 1)
				return (0);
		i++;
	}
	return (1);
}

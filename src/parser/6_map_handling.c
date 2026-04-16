/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_map_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:23 by craabe            #+#    #+#             */
/*   Updated: 2026/04/16 16:01:44 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	strip_newlines_spaces(t_settings *settings)
{
	size_t	i;
	size_t	j;
	char	**map_array;

	map_array = settings->map_info->map;
	i = 0;
	while (map_array[i])
	{
		j = ft_strlen(map_array[i]) - 1;
		while (j > 0 && (map_array[i][j] == ' ' || map_array[i][j] == '\t'
				|| map_array[i][j] == '\n' || map_array[i][j] == '\r'))
			j--;
		map_array[i][j + 1] = '\0';
		i++;
	}
}

static unsigned int	get_map_width(t_settings *settings)
{
	size_t	width;
	size_t	len;
	int		i;
	char	**map;

	width = 0;
	i = 0;
	map = settings->map_info->map;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (width < len)
			width = len;
		i++;
	}
	return (width);
}

static int	format_map(t_settings *settings)
{
	if (left_align_map(settings) != 1)
		return (0);
	strip_newlines_spaces(settings);
	settings->map_info->x_width = get_map_width(settings);
	if (add_padding(settings) != 1)
		return (0);
	return (1);
}

int	add_map_info(t_settings *settings, t_map_list *map_list)
{
	char		**map_array;
	size_t		i;
	t_map_node	*current;

	settings->map_info->y_height = map_list->size;
	map_array = ft_calloc(settings->map_info->y_height + 1, sizeof(char *));
	if (!map_array)
		return (0);
	settings->map_info->map = map_array;
	i = 0;
	current = map_list->first;
	while (i < settings->map_info->y_height)
	{
		settings->map_info->map[i] = ft_strdup(current->line);
		if (!settings->map_info->map[i])
			return (0);
		i++;
		current = current->next;
	}
	settings->map_info->map[i] = NULL;
	return (format_map(settings));
}

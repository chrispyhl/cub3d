/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_map_verification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:31 by craabe            #+#    #+#             */
/*   Updated: 2026/04/16 17:11:02 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_player_info(t_settings *settings, int i, int j, char dir)
{
	if (settings->player_info->dir != 'x')
		return (0);
	settings->player_info->dir = dir;
	settings->player_info->player_x = ((double)j) + 0.5;
	settings->player_info->player_y = ((double)i) + 0.5;
	settings->map_info->map[i][j] = '0';
	return (1);
}

static int	verify_contents(t_settings *settings)
{
	size_t	i;
	size_t	j;
	char	current_char;

	i = 0;
	while (settings->map_info->map[i])
	{
		j = 0;
		while (settings->map_info->map[i][j])
		{
			current_char = settings->map_info->map[i][j];
			if (current_char != 'N' && current_char != 'S'
				&& current_char != 'W' && current_char != 'E'
				&& current_char != '1' && current_char != '0'
				&& current_char != ' ')
				return (print_map_ver_error_msg(1));
			else if (current_char == 'N' || current_char == 'S'
				|| current_char == 'W' || current_char == 'E')
				if (add_player_info(settings, i, j, current_char) != 1)
					return (print_map_ver_error_msg(2));
			j++;
		}
		i++;
	}
	return (1);
}

int	verify_map_info(t_settings *settings)
{
	if (verify_contents(settings) != 1)
		return (0);
	if (settings->player_info->dir == 'x')
		return (print_map_ver_error_msg(3));
	if (verify_borders(settings) != 1)
		return (print_map_ver_error_msg(5));
	return (1);
}

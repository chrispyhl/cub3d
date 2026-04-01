/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_color_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:17 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 14:43:31 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	generate_color_code(char **values)
{
	int	i;
	int	j;
	int	red;
	int	green;
	int	blue;

	i = 0;
	while (values[i])
	{
		j = 0;
		while (values[i][j])
		{
			if (ft_isdigit(values[i][j]) != 1)
				return (-1);
			j++;
		}
		i++;
	}
	red = ft_atoi(values[0]);
	green = ft_atoi(values[1]);
	blue = ft_atoi(values[2]);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
		|| blue > 255)
		return (-1);
	return (red << 16 | green << 8 | blue);
}

static int	convert_color_info(char *code_str)
{
	int		i;
	char	**values;
	int		code;

	values = ft_split(code_str, ',');
	if (!values)
		return (-1);
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
		code = -1;
	else
		code = generate_color_code(values);
	free_array(values);
	return (code);
}

int	verify_color_info(t_settings *settings)
{
	int	valid_flag;

	valid_flag = 1;
	if (settings->color_info->floor_color == -1)
	{
		ft_putstr_fd("ERROR:\nCouldn't generate color code for floor.\n", 1);
		valid_flag = 0;
	}
	if (settings->color_info->ceil_color == -1)
	{
		ft_putstr_fd("ERROR:\nCouldn't generate color code for ceiling.\n", 1);
		valid_flag = 0;
	}
	return (valid_flag);
}

int	add_color_info(t_settings *settings, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (settings->color_info->floor_color != -1)
		{
			ft_putstr_fd("ERROR:\nMultiple floor color codes.\n", 1);
			return (0);
		}
		settings->color_info->floor_color = convert_color_info(line + 2);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (settings->color_info->ceil_color != -1)
		{
			ft_putstr_fd("ERROR:\nMultiple ceiling color codes.\n", 1);
			return (0);
		}
		settings->color_info->ceil_color = convert_color_info(line + 2);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cub3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:44 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 09:55:47 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/main.h"

int	main(int argc, char *argv[])
{
	t_settings	*settings;

	if (argc != 2)
	{
		if (argc < 2)
			ft_putstr_fd("No argument!\n", 1);
		else
			ft_putstr_fd("Too many arguments!\n", 1);
		return (1);
	}
	settings = create_settings(argv[1]);
	if (!settings)
		return (1);
	// settings go to ENGINE here

	ft_printf(".cub: '%s'\n", settings->cub_path);
	ft_printf("NO: '%s'\n", settings->tex_info->no_tex);
	ft_printf("SO: '%s'\n", settings->tex_info->so_tex);
	ft_printf("WE: '%s'\n", settings->tex_info->we_tex);
	ft_printf("EA: '%s'\n\n", settings->tex_info->ea_tex);
	ft_printf("Floor: %i\n", settings->color_info->floor_color);
	ft_printf("Ceiling: %i\n\n", settings->color_info->ceil_color);
	ft_printf("Map:\n");

	int i;
	i = 0;
	while (settings->map_info->map[i])
	{
		printf("'%s'\n", settings->map_info->map[i]);
		i++;
	}

	free_settings(settings);
	return (0);
}

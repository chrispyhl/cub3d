/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cub3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:44 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 15:03:10 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/parser.h"

/*
terminal command:

 valgrind --leak-check=full ./cub3D ./cub_files/invalid/duplicate_tex.cub ./cub_files/invalid/phase_violation.cub ./cub_files/invalid/fractured_map.cub ./cub_files/invalid/missing_info.cub ./cub_files/invalid/invalid_content.cub ./cub_files/invalid/no_map.cub ./cub_files/valid/garbage_padding.cub
*/

// static void	print_parsed_settings(t_settings *settings)
// {
// 	int	i;

// 	ft_printf("\n--- PARSED DATA ---\n");
// 	ft_printf("NO: '%s'\n", settings->tex_info->no_tex);
// 	ft_printf("SO: '%s'\n", settings->tex_info->so_tex);
// 	ft_printf("WE: '%s'\n", settings->tex_info->we_tex);
// 	ft_printf("EA: '%s'\n", settings->tex_info->ea_tex);
// 	ft_printf("Floor Color:  %d\n", settings->color_info->floor_color);
// 	ft_printf("Ceil Color:   %d\n", settings->color_info->ceil_color);
// 	// Cast size_t to unsigned int just to be safe with standard ft_printf
// 	ft_printf("Map Width:    %u\n", (unsigned int)settings->map_info->x_width);
// 	ft_printf("Map Height:   %u\n", (unsigned int)settings->map_info->y_height);
// 	ft_printf("Map Preview:\n");
// 	i = 0;
// 	while (settings->map_info->map && settings->map_info->map[i])
// 	{
// 		ft_printf("[%d] '%s'\n", i, settings->map_info->map[i]);
// 		i++;
// 	}
// 	ft_printf("-------------------\n");
// }

// int	main(int argc, char **argv)
// {
// 	t_settings	*settings;
// 	int			i;

// 	if (argc < 2)
// 	{
// 		ft_putstr_fd("Error\nUsage: ./cub3D_tester <file1.cub> <file2.cub> ...\n",
// 			2);
// 		return (1);
// 	}
// 	i = 1;
// 	while (i < argc)
// 	{
// 		ft_printf("\n========================================\n");
// 		ft_printf("TESTING [%d/%d]: %s\n", i, argc - 1, argv[i]);
// 		ft_printf("========================================\n");
// 		settings = create_settings(argv[i]);
// 		if (settings)
// 		{
// 			ft_printf("\n✅ [SUCCESS] File parsed perfectly!\n");
// 			print_parsed_settings(settings);
// 			free_settings(settings);
// 		}
// 		else
// 		{
// 			ft_printf("\n❌ [REJECTED] Parser correctly caught the error and aborted.\n");
// 		}
// 		i++;
// 	}
// 	return (0);
// }

#include "../../inc/main.h"

int	main(int argc, char *argv[])
{
	t_settings	*settings;
	int			i;

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
	i = 0;
	while (settings->map_info->map[i])
	{
		printf("'%s'\n", settings->map_info->map[i]);
		i++;
	}
	printf("x: %zu\n", settings->map_info->x_width);
	printf("y: %zu\n", settings->map_info->y_height);
	printf("\n");
	printf("player direction: %c\n", settings->player_info->dir);
	printf("player x coord: %f\n", settings->player_info->player_x);
	printf("player y coord: %f\n", settings->player_info->player_y);
	free_settings(settings);
	return (0);
}

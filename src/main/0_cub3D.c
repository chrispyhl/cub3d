/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cub3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:44 by craabe            #+#    #+#             */
/*   Updated: 2026/04/03 18:11:12 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/main.h"
// #include <stdio.h>
// #include <stdlib.h>

// /* Replace this with your actual cub3d header file */
// /* #include "cub3d.h" */

// #define GREEN "\033[0;32m"
// #define RED "\033[0;31m"
// #define RESET "\033[0m"

// /* Dummy declarations to illustrate the structure. Remove these if using your header. */
// typedef struct s_settings t_settings;
// t_settings  *create_settings(char *arg);
// void        free_settings(t_settings *settings); 

// void    test_maps(char **maps, int expect_valid)
// {
//     int         i;
//     t_settings  *result;

//     i = 0;
//     while (maps[i] != NULL)
//     {
//         printf("Testing: %s\n-> ", maps[i]);
        
//         result = create_settings(maps[i]);
        
//         if (expect_valid == 1)
//         {
//             if (result != NULL)
//             {
//                 printf(GREEN "OK\n" RESET);
//                 free_settings(result);
//             }
//             else
//                 printf(RED "KO (Expected Valid, got Invalid)\n" RESET);
//         }
//         else
//         {
//             if (result == NULL)
//                 printf(GREEN "OK (Properly rejected)\n" RESET);
//             else
//             {
//                 printf(RED "KO (Invalid map was accepted!)\n" RESET);
//                 free_settings(result);
//             }
//         }
//         printf("----------------------------------------\n");
//         i++;
//     }
// }

// int main(void)
// {
//     char *invalid_maps[] = {
//         "cub_files/invalid/duplicate_tex.cub",
//         "cub_files/invalid/fractured_map.cub",
//         "cub_files/invalid/invalid_border.cub",
//         "cub_files/invalid/invalid_border2.cub",
//         "cub_files/invalid/invalid_content.cub",
//         "cub_files/invalid/invalid_unreachable_room.cub",
//         "cub_files/invalid/missing_info.cub",
//         "cub_files/invalid/missing_player.cub",
//         "cub_files/invalid/multiple_players.cub",
//         "cub_files/invalid/no_map.cub",
//         "cub_files/invalid/phase_violation.cub",
//         NULL
//     };

//     char *valid_maps[] = {
//         "cub_files/valid/cornerless.cub",
//         "cub_files/valid/garbage_padding.cub",
//         "cub_files/valid/standard.cub",
//         "cub_files/valid/ugly.cub",
//         "cub_files/valid/unreachable_rooms.cub",
//         NULL
//     };

//     printf("=== RUNNING INVALID MAP TESTS ===\n");
//     test_maps(invalid_maps, 0);
    
//     printf("\n=== RUNNING VALID MAP TESTS ===\n");
//     test_maps(valid_maps, 1);
    
//     return (0);
// }

// #include "../../inc/main.h"

// int	main(int argc, char *argv[])
// {
// 	t_settings	*settings;
// 	int			i;

// 	if (argc != 2)
// 	{
// 		if (argc < 2)
// 			ft_putstr_fd("No argument!\n", 1);
// 		else
// 			ft_putstr_fd("Too many arguments!\n", 1);
// 		return (1);
// 	}
// 	settings = create_settings(argv[1]);
// 	if (!settings)
// 		return (1);
// 	// settings go to ENGINE here
// 	ft_printf(".cub: '%s'\n", settings->cub_path);
// 	ft_printf("NO: '%s'\n", settings->tex_info->no_tex);
// 	ft_printf("SO: '%s'\n", settings->tex_info->so_tex);
// 	ft_printf("WE: '%s'\n", settings->tex_info->we_tex);
// 	ft_printf("EA: '%s'\n\n", settings->tex_info->ea_tex);
// 	ft_printf("Floor: %i\n", settings->color_info->floor_color);
// 	ft_printf("Ceiling: %i\n\n", settings->color_info->ceil_color);
// 	ft_printf("Map:\n");
// 	i = 0;
// 	while (settings->map_info->map[i])
// 	{
// 		printf("'%s'\n", settings->map_info->map[i]);
// 		i++;
// 	}
// 	printf("x: %zu\n", settings->map_info->x_width);
// 	printf("y: %zu\n", settings->map_info->y_height);
// 	printf("\n");
// 	printf("player direction: %c\n", settings->player_info->dir);
// 	printf("player x coord: %f\n", settings->player_info->player_x);
// 	printf("player y coord: %f\n", settings->player_info->player_y);
// 	free_settings(settings);
// 	return (0);
// }

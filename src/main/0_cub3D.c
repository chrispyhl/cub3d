/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cub3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:44 by craabe            #+#    #+#             */
/*   Updated: 2026/04/03 18:44:31 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/main.h"
// #include <stdio.h>
// #include <stdlib.h>

// #define GREEN "\033[0;32m"
// #define RED "\033[0;31m"
// #define RESET "\033[0m"

// /* Struct to tie a filepath directly to its expected result */
// typedef struct s_test_case {
//     char    *filepath;
//     int     expect_valid; // 1 for valid, 0 for invalid
// } t_test_case;

// int main(void)
// {
//     t_test_case tests[] = {
//         // Invalid Maps
//         {"cub_files/invalid/duplicate_texture.cub", 0},
//         {"cub_files/invalid/fractured_map.cub", 0},
//         {"cub_files/invalid/invalid_border.cub", 0},
//         {"cub_files/invalid/invalid_border2.cub", 0},
//         {"cub_files/invalid/invalid_color_code.cub", 0},
//         {"cub_files/invalid/invalid_line.cub", 0},
//         {"cub_files/invalid/invalid_unreachable_room.cub", 0},
//         {"cub_files/invalid/missing_color_code.cub", 0},
//         {"cub_files/invalid/missing_player.cub", 0},
//         {"cub_files/invalid/missing_texture.cub", 0},
//         {"cub_files/invalid/multiple_players.cub", 0},
//         {"cub_files/invalid/no_map.cub", 0},
//         {"cub_files/invalid/texture_after_map.cub", 0},

//         // Valid Maps
//         {"cub_files/valid/.cub", 1},
//         {"cub_files/valid/cornerless.cub", 1},
//         {"cub_files/valid/garbage_padding.cub", 1},
//         {"cub_files/valid/standard.cub", 1},
//         {"cub_files/valid/ugly.cub", 1},
//         {"cub_files/valid/unreachable_rooms.cub", 1}
//     };

//     // Automatically calculate the number of tests based on the array size
//     int num_tests = sizeof(tests) / sizeof(tests[0]);
//     int passed = 0;

//     printf("=== CUB3D PARSER TEST SUITE ===\n\n");

//     for (int i = 0; i < num_tests; i++)
//     {
//         printf("Testing [%d/%d]: %s\n", i + 1, num_tests, tests[i].filepath);
        
//         t_settings *result = create_settings(tests[i].filepath);
//         int is_valid = (result != NULL); // Evaluates to 1 if not NULL, 0 if NULL

//         // Check if the actual result matches the expected result
//         if (is_valid == tests[i].expect_valid)
//         {
//             printf(GREEN "  [OK] " RESET);
//             if (is_valid) 
//                 printf("Valid map parsed successfully.\n");
//             else 
//                 printf("Invalid map properly rejected.\n");
            
//             passed++;
//         }
//         else
//         {
//             printf(RED "  [KO] " RESET);
//             if (tests[i].expect_valid) 
//                 printf("Expected valid map, but got NULL (rejected).\n");
//             else 
//                 printf("Expected invalid map, but got a t_settings struct (accepted).\n");
//         }

//         // Clean up memory if a struct was actually created
//         if (result != NULL)
//             free_settings(result);
        
//         printf("--------------------------------------------------\n");
//     }

//     // Print final summary
//     printf("\n=== TEST SUMMARY ===\n");
//     if (passed == num_tests)
//         printf(GREEN "%d/%d TESTS PASSED. FLAWLESS VICTORY!\n" RESET, passed, num_tests);
//     else
//         printf(RED "%d/%d TESTS PASSED. CHECK FAILURES ABOVE.\n" RESET, passed, num_tests);

//     return (0);
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

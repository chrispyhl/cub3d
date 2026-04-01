/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:29 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 10:45:45 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "main.h"

typedef enum e_cub_content
{
	TEXTURE,
	COLOR,
	MAP
}						t_cub_content;

// linked list for map lines (will become string array in main struct t_settings)
typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}						t_map_node;

typedef struct s_map_list
{
	t_map_node			*first;
	t_map_node			*last;
	size_t				size;
	int					map_parsed;
}						t_map_list;

// SETTINGS CREATION
int						add_tex_info(t_settings *settings, char *line);
int						add_color_info(t_settings *settings, char *line);
int						add_map_info(t_settings *settings,
							t_map_list *map_list);

// parsing
int						parse_cub(t_settings *settings);

// VERIFICATION
int						verify_tex_info(t_settings *settings);
int						verify_color_info(t_settings *settings);
int						verify_map_info(t_settings *settings);

// MISC UTILITY
int						handle_cub_path(char *path, t_settings *settings);
char					*trim_space_tabs(char *path);
char					*sanitize_line(char *line);

// MAP LIST UTILITY
t_map_list				*populate_map_list(void);
void					free_map_list(t_map_list *map_list);
int						add_map_node(t_map_list *map_list, char *line);

// MAP VERIFICATION
int						verify_map(t_settings *settings);

#endif

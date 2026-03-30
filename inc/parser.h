

#ifndef PARSER_H
# define PARSER_H

# include "main.h"

typedef enum e_error_type
{
	GEN_ERR, // 0 = generic error
	NO_ERR,  // 1 = no error

}		t_error_type;

// SETTINGS CREATION
int		add_tex_info(t_settings *settings, char *line);
int		add_color_info(t_settings *settings, char *line);

// VERIFICATION
int		verify_tex_info(t_settings *settings);
int		verify_color_info(t_settings *settings);

// UTILITY
int		handle_cub_path(char *path, t_settings *settings);
char	*trim_space_tabs(char *path);
char	*sanitize_line(char *line);

#endif

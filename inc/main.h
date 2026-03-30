
#ifndef MAIN_H
# define MAIN_H

# include "defines.h"
# include "includes.h"
# include "settings.h"

// PARSER
t_settings	*create_settings(char *arg);

// GENERAL UTILITY
void		free_settings(t_settings *settings);
void		free_array(char **array);

#endif

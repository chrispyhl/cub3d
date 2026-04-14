/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:25 by craabe            #+#    #+#             */
/*   Updated: 2026/04/14 18:02:57 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "settings.h"

# include "../libft/src/libft.h"
# include <stdint.h> // for MAX_SIZE
# include <math.h> // for fabs

// PARSER
t_settings	*create_settings(char *arg);

// GENERAL UTILITY
void		free_settings(t_settings *settings);
void		free_array(char **array);

#endif

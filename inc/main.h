/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:25 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 09:55:27 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

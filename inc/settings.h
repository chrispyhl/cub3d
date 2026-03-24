/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:07:42 by craabe            #+#    #+#             */
/*   Updated: 2026/03/24 17:08:56 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

typedef struct s_tex_info
{
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			*ea_tex;
}					t_tex_info;

typedef struct s_color_info
{
	char			*floor_color;
	char			*ceil_color;
}					t_color_info;

typedef struct s_settings
{
	char			**map;

	t_tex_info		tex_info;
	t_color_info	color_info;

}					t_settings;

#endif

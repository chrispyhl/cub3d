/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:09:12 by cpohl             #+#    #+#             */
/*   Updated: 2026/04/14 15:19:22 by cpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_bonus.h"

void	free_tex(t_engine *eng)
{
	if (eng->no_tex_img)
		mlx_delete_texture(eng->no_tex_img);
	if (eng->so_tex_img)
		mlx_delete_texture(eng->so_tex_img);
	if (eng->we_tex_img)
		mlx_delete_texture(eng->we_tex_img);
	if (eng->ea_tex_img)
		mlx_delete_texture(eng->ea_tex_img);
	eng->no_tex_img = NULL;
	eng->so_tex_img = NULL;
	eng->we_tex_img = NULL;
	eng->ea_tex_img = NULL;
}

int	load_tex(t_engine *eng)
{
	eng->no_tex_img = mlx_load_png(eng->settings->tex_info->no_tex);
	if (!eng->no_tex_img)
		return (0);
	eng->so_tex_img = mlx_load_png(eng->settings->tex_info->so_tex);
	if (!eng->so_tex_img)
		return (free_tex(eng), 0);
	eng->we_tex_img = mlx_load_png(eng->settings->tex_info->we_tex);
	if (!eng->we_tex_img)
		return (free_tex(eng), 0);
	eng->ea_tex_img = mlx_load_png(eng->settings->tex_info->ea_tex);
	if (!eng->ea_tex_img)
		return (free_tex(eng), 0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_texture_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:10 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 10:16:00 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static void	print_tex_error_msg(int code)
{
	if (code == 0)
		ft_putstr_fd("ERROR: Texture for north wall missing,"
						" invalid or inaccessable.\n",
						1);
	else if (code == 1)
		ft_putstr_fd("ERROR: Texture for south wall missing,"
						" invalid or inaccessable.\n",
						1);
	else if (code == 2)
		ft_putstr_fd("ERROR: Texture for west wall missing,"
						" invalid or inaccessable.\n",
						1);
	else if (code == 3)
		ft_putstr_fd("ERROR: Texture for east wall missing,"
						" invalid or inaccessable.\n",
						1);
}

static int	return_tex_dup_error(int code)
{
	if (code == 0)
		ft_putstr_fd("ERROR: Duplicate texture for north wall.\n", 1);
	else if (code == 1)
		ft_putstr_fd("ERROR: Duplicate texture for south wall.\n", 1);
	else if (code == 2)
		ft_putstr_fd("ERROR: Duplicate texture for west wall.\n", 1);
	else if (code == 3)
		ft_putstr_fd("ERROR: Duplicate texture for east wall.\n", 1);
	return (0);
}

static int	check_tex_access(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	verify_tex_info(t_settings *settings)
{
	char	*paths[4];
	int		i;
	int		valid_flag;

	paths[0] = settings->tex_info->no_tex;
	paths[1] = settings->tex_info->so_tex;
	paths[2] = settings->tex_info->we_tex;
	paths[3] = settings->tex_info->ea_tex;
	i = 0;
	valid_flag = 1;
	while (i < 4)
	{
		if (!paths[i] || check_tex_access(paths[i]) != 1)
		{
			print_tex_error_msg(i);
			valid_flag = 0;
		}
		i++;
	}
	return (valid_flag);
}

int	add_tex_info(t_settings *settings, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (settings->tex_info->no_tex != NULL)
			return (return_tex_dup_error(0));
		settings->tex_info->no_tex = ft_substr(line, 3, ft_strlen(line) - 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (settings->tex_info->so_tex != NULL)
			return (return_tex_dup_error(1));
		settings->tex_info->so_tex = ft_substr(line, 3, ft_strlen(line) - 3);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (settings->tex_info->we_tex != NULL)
			return (return_tex_dup_error(2));
		settings->tex_info->we_tex = ft_substr(line, 3, ft_strlen(line) - 3);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (settings->tex_info->ea_tex != NULL)
			return (return_tex_dup_error(3));
		settings->tex_info->ea_tex = ft_substr(line, 3, ft_strlen(line) - 3);
	}
	return (1);
}

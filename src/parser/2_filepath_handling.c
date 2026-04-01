/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_filepath_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:01 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 09:56:03 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	check_filetype(char *path)
{
	char	*path_end;

	path_end = ft_strrchr(path, '.');
	// found no dot --> can't end in .cub
	if (!path_end)
		return (0);
	// last 5 chars .cub and null terminator? --> .cub verified
	if (ft_strncmp(path_end, ".cub", 5) != 0)
		return (0);
	return (1);
}

int	handle_cub_path(char *path, t_settings *settings)
{
	int fd;
	char *stripped_path;

	stripped_path = trim_space_tabs(path);
	if (!stripped_path)
	{
		ft_putstr_fd("ERROR: Invalid filepath.\n", 1);
		return (0);
	}
	if (check_filetype(stripped_path) != 1)
	{
		ft_putstr_fd("ERROR: Not a .cub file.\n", 1);
		free(stripped_path);
		return (0);
	}
	fd = open(stripped_path, O_RDONLY);
	if (fd == -1)
	{
		free(stripped_path);
		ft_putstr_fd("ERROR: Can't open file.\n", 1);
		return (0);
	}
	close(fd);
	settings->cub_path = stripped_path;
	return (1);
}

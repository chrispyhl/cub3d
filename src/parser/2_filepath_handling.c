/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_filepath_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:01 by craabe            #+#    #+#             */
/*   Updated: 2026/04/03 18:10:07 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	return_filepath_error(int code)
{
	if (code == 0)
		ft_putstr_fd("ERROR:\nInvalid filepath.\n", 1);
	else if (code == 1)
		ft_putstr_fd("ERROR:\nNot a .cub file.\n", 1);
	else if (code == 2)
		ft_putstr_fd("ERROR:\nCan't open file.\n", 1);
	else if (code == 3)
		ft_putstr_fd("ERROR:\nMalloc error during filepath check.\n", 1);
	return (0);
}

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

static void	hidden_file_warning(char *stripped_path)
{
	char	*filename;

	filename = ft_strrchr(stripped_path, '/') + 1;
	if (ft_strncmp(stripped_path, ".cub", 5) == 0 || ft_strncmp(filename,
			".cub", 5) == 0)
		ft_putstr_fd("WARNING:\nFilename \".cub\" (hidden file)"
			" might cause issues in some environments.\n", 1);
}

int	handle_cub_path(char *path, t_settings *settings)
{
	int		fd;
	char	*stripped_path;

	stripped_path = trim_space_tabs(path);
	if (!stripped_path)
		return (return_filepath_error(0));
	if (check_filetype(stripped_path) != 1)
	{
		free(stripped_path);
		return (return_filepath_error(1));
	}
	fd = open(stripped_path, O_RDONLY);
	if (fd == -1)
	{
		free(stripped_path);
		return (return_filepath_error(2));
	}
	close(fd);
	hidden_file_warning(stripped_path);
	settings->cub_path = stripped_path;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:05:25 by craabe            #+#    #+#             */
/*   Updated: 2026/03/27 17:56:01 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: shorten paths when Makefile is ready
#include "../../inc/defines.h"
#include "../../inc/includes.h"
#include "../../inc/settings.h"

#ifndef PATH
# define PATH "./cub/valid/example.cub      "
#endif

#ifndef INVAL_PATH
# define INVAL_PATH "invalid"
#endif

static char	*strip_path(char *path)
{
	char	*stripped_path;
	int		start;
	int		end;

	start = 0;
	while (path[start] == ' ' || path[start] == '\t')
		start++;
	if (path[start] == '\0')
		return (NULL);
	end = ft_strlen(path) - 1;
	while (path[end] == ' ' || path[end] == '\t')
		end--;
	stripped_path = ft_substr(path, start, end - start + 1);
	if (!stripped_path)
		return (NULL);
	if (ft_strchr(stripped_path, ' ') != NULL || ft_strchr(stripped_path,
			'\t') != NULL)
	{
		free(stripped_path);
		return (NULL);
	}
	return (stripped_path);
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

static int	verify_argument(char *path)
{
	int		fd;
	char	*stripped_path;

	stripped_path = strip_path(path);
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
	free(stripped_path);
	return (1);
}

int	main(int argc, char *argv[])
{
	char	*arg;

	if (argc != 2)
	{
		if (argc < 2)
			ft_putstr_fd("No argument!\n", 1);
		if (argc > 2)
			ft_putstr_fd("Too many arguments!\n", 1);
		return (1);
	}
	arg = argv[1];
	if (verify_argument(arg) == 1)
	{
		ft_putstr_fd("All good!\n", 1);
		return (0);
	}
	else
	{
		ft_putstr_fd("Something not good!\n", 1);
		return (1);
	}
}

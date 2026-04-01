/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cub_sanitizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:05 by craabe            #+#    #+#             */
/*   Updated: 2026/04/01 11:25:44 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*trim_space_tabs(char *line)
{
	char	*stripped_path;
	int		start;
	int		end;

	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	if (line[start] == '\0')
		return (NULL);
	end = ft_strlen(line) - 1;
	while (line[end] == ' ' || line[end] == '\t')
		end--;
	stripped_path = ft_substr(line, start, end - start + 1);
	if (!stripped_path)
		return (NULL);
	return (stripped_path);
}

static void	tabs_to_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

static char	*shorten_spaces(char *full_str, int str_len)
{
	int		i;
	int		j;
	char	*short_str;

	short_str = malloc((str_len + 1) * sizeof(char));
	if (!short_str)
		return (NULL);
	i = 0;
	j = 0;
	while (j < str_len)
	{
		// TODO: decide:
		// thought I needed escaped space handling but mb not?
		// if (full_str[j] == '\\' && full_str[j + 1] == ' ')
		// 	j++;
		if (full_str[j] == '\n' || full_str[j] == '\r')
			break ;
		short_str[i] = full_str[j];
		i++;
		j++;
		while (full_str[j] == ' ' && full_str[j - 1] == ' ')
			j++;
	}
	short_str[i] = '\0';
	return (short_str);
}

char	*sanitize_line(char *line)
{
	char	*stripped;
	int		stripped_len;
	char	*sanitized;

	stripped = trim_space_tabs(line);
	if (!stripped)
		return (NULL);
	tabs_to_spaces(stripped);
	stripped_len = ft_strlen(stripped);
	sanitized = shorten_spaces(stripped, stripped_len);
	if (!sanitized)
	{
		free(stripped);
		return (NULL);
	}
	free(stripped);
	return (sanitized);
}

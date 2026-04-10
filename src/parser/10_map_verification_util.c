
#include "../../inc/parser.h"

int	print_tex_ver_error_msg(int code)
{
	if (code == 0)
		ft_putstr_fd("ERROR:\nMap too small or missing.\n", 1);
	if (code == 1)
		ft_putstr_fd("ERROR:\nMap contains invalid content.\n", 1);
	else if (code == 2)
		ft_putstr_fd("ERROR:\nToo many players on map.\n", 1);
	else if (code == 3)
		ft_putstr_fd("ERROR:\nNo player on map.\n", 1);
	else if (code == 4)
		ft_putstr_fd("ERROR:\nDuplicate allocation failed.\n", 1);
	else if (code == 5)
		ft_putstr_fd("ERROR:\nMap border(s) inconsistent.\n", 1);
	return (0);
}

static void	flood_fill(char **map, size_t x, size_t y, t_settings *settings)
{
	if (settings->map_info->spill_flag == 0)
	{
		if (y >= settings->map_info->y_height
			|| x >= ft_strlen(settings->map_info->map[y]))
		{
			settings->map_info->spill_flag = 1;
			return ;
		}
		else if (map[y][x] == ' ')
		{
			settings->map_info->spill_flag = 1;
			return ;
		}
		else if (map[y][x] == '1' || map[y][x] == 'F')
			return ;
		else
			map[y][x] = 'F';
		flood_fill(map, x + 1, y, settings);
		if (x > 0)
			flood_fill(map, x - 1, y, settings);
		flood_fill(map, x, y + 1, settings);
		if (y > 0)
			flood_fill(map, x, y - 1, settings);
	}
}

static int	check_backrooms(char **map, t_settings *settings)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				flood_fill(map, j, i, settings);
				if (settings->map_info->spill_flag == 1)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static char	**duplicate_map(t_settings *settings)
{
	char	**dup;
	size_t	i;

	dup = ft_calloc(settings->map_info->y_height + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (settings->map_info->map[i])
	{
		dup[i] = ft_strdup(settings->map_info->map[i]);
		if (!dup[i])
		{
			free_array(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

int	verify_borders(t_settings *settings)
{
	char	**dup;

	dup = duplicate_map(settings);
	if (!dup)
		return (print_tex_ver_error_msg(4));
	flood_fill(dup, settings->player_info->player_x,
		settings->player_info->player_y, settings);
	if (settings->map_info->spill_flag == 1)
	{
		free_array(dup);
		return (0);
	}
	if (check_backrooms(dup, settings) != 1)
	{
		free_array(dup);
		return (0);
	}
	free_array(dup);
	return (1);
}

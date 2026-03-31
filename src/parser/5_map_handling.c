
#include "../../inc/parser.h"

// TODO: add more checks!
int	verify_map_info(t_settings *settings)
{
	if (settings->map_info->x_width == 0 || settings->map_info->y_height == 0 || !settings->map_info->map)
		return (0);
	return (1);
}

static unsigned int	get_map_width(t_map_list *map_list)
{
	t_map_node	*current;
	size_t		width;
	size_t		len;

	current = map_list->first;
	width = 0;
	while (current)
	{
		len = ft_strlen(current->line);
		if (len > width)
			width = len;
		current = current->next;
	}
	return (width);
}

static void strip_newlines(t_settings *settings)
{
	size_t i;
	size_t j;
	char **map_array;

	map_array = settings->map_info->map;
	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (map_array[i][j])
		{
			if (map_array[i][j] == '\n')
				map_array[i][j] = '\0';
			j++;
		}
		i++;
	}
}

int	add_map_info(t_settings *settings, t_map_list *map_list)
{
	char	**map_array;
	size_t i;
	t_map_node *current;

	settings->map_info->y_height = map_list->size;
	settings->map_info->x_width = get_map_width(map_list);
	// + 1 for NULL terminator at end of array
	map_array = ft_calloc(settings->map_info->y_height + 1, sizeof(char *));
	if (!map_array)
		return (0);
	settings->map_info->map = map_array;
	i = 0;
	current = map_list->first;
	while (i < settings->map_info->y_height)
	{
		settings->map_info->map[i] = ft_strdup(current->line);
		if (!settings->map_info->map[i])
			return (0);
		i++;
		current = current->next;
	}
	settings->map_info->map[i] = NULL;
	strip_newlines(settings);
	return (1);
}

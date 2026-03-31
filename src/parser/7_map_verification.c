
#include "../../inc/parser.h"

// static int	check_chars(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j] == ' ')
// 			j++;
// 		if (map[i][j] != '1' || map[i][ft_strlen(map[i] - 1)])
// 		i++;
// 	}
// 	return (1);
// }

int	verify_map_info(t_settings *settings)
{
	if (settings->map_info->x_width < 3 || settings->map_info->y_height < 3
		|| !settings->map_info->map)
		return (0);
	// if (verify_map(settings) != 1)
	// 	return (0);
	return (1);
}

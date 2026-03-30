
#include "../../inc/defines.h"
#include "../../inc/includes.h"
#include "../../inc/settings.h"

void	free_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_settings(t_settings *settings)
{
	if (settings)
	{
		if (settings->cub_path)
			free(settings->cub_path);
		if (settings->tex_info)
		{
			if (settings->tex_info->no_tex)
				free(settings->tex_info->no_tex);
			if (settings->tex_info->so_tex)
				free(settings->tex_info->so_tex);
			if (settings->tex_info->we_tex)
				free(settings->tex_info->we_tex);
			if (settings->tex_info->ea_tex)
				free(settings->tex_info->ea_tex);
			free(settings->tex_info);
		}
		if (settings->color_info)
			free(settings->color_info);
		if (settings->map_info)
		{
			// includes check for array existance already
			free_array(settings->map_info->map);
			free(settings->map_info);
		}
		free(settings);
	}
}

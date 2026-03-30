

#include "../../inc/parser.h"

int	main(int argc, char *argv[])
{
	t_settings	*settings;

	if (argc != 2)
	{
		if (argc < 2)
			ft_putstr_fd("No argument!\n", 1);
		else
			ft_putstr_fd("Too many arguments!\n", 1);
		return (1);
	}
	settings = create_settings(argv[1]);
	if (!settings)
		return (1);
	// settings go to ENGINE here

	ft_printf(".cub: '%s'\n", settings->cub_path);
	ft_printf("NO: '%s'\n", settings->tex_info->no_tex);
	ft_printf("SO: '%s'\n", settings->tex_info->so_tex);
	ft_printf("WE: '%s'\n", settings->tex_info->we_tex);
	ft_printf("EA: '%s'\n", settings->tex_info->ea_tex);
	ft_printf("Floor: %i\n", settings->color_info->floor_color);
	ft_printf("Ceiling: %i\n", settings->color_info->ceil_color);

	free_settings(settings);
	return (0);
}

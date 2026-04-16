/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cub3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:55:44 by craabe            #+#    #+#             */
/*   Updated: 2026/04/16 15:42:21 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/engine.h"
#include "../../inc/main.h"

int	main(int argc, char *argv[])
{
	t_settings	*settings;
	int			status;

	if (argc != 2)
	{
		if (argc < 2)
			ft_putstr_fd("ERROR\nNo argument!\n", 1);
		else
			ft_putstr_fd("ERROR\nToo many arguments!\n", 1);
		return (1);
	}
	settings = create_settings(argv[1]);
	if (!settings)
		return (1);
	status = start_engine(settings);
	free_settings(settings);
	return (status);
}

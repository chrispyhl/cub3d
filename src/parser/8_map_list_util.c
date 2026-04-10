/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_map_list_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gries <gries@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 09:56:27 by craabe            #+#    #+#             */
/*   Updated: 2026/04/03 18:09:17 by gries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	free_map_list(t_map_list *map_list)
{
	t_map_node	*current;
	t_map_node	*next_node;

	if (!map_list)
		return ;
	current = map_list->first;
	while (current)
	{
		next_node = current->next;
		if (current->line)
			free(current->line);
		free(current);
		current = next_node;
	}
	map_list->first = NULL;
	map_list->last = NULL;
	map_list->size = 0;
	free(map_list);
}

t_map_list	*populate_map_list(void)
{
	t_map_list	*map_list;

	map_list = malloc(sizeof(t_map_list));
	map_list->first = NULL;
	map_list->last = NULL;
	map_list->size = 0;
	map_list->map_parsed = 0;
	return (map_list);
}

static t_map_node	*create_map_node(char *line)
{
	t_map_node	*map_node;

	map_node = malloc(sizeof(t_map_node));
	if (!map_node)
		return (NULL);
	map_node->line = ft_strdup(line);
	if (!map_node->line)
		return (NULL);
	map_node->next = NULL;
	return (map_node);
}

int	add_map_node(t_map_list *map_list, char *line)
{
	t_map_node	*map_node;

	map_node = create_map_node(line);
	if (!map_node)
		return (0);
	if (map_list->size == 0)
	{
		map_list->first = map_node;
		map_list->last = map_node;
	}
	else
	{
		map_list->last->next = map_node;
		map_list->last = map_node;
	}
	map_list->size++;
	return (1);
}

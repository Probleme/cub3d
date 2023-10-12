/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 05:58:09 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/12 22:15:22 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_init_struct(t_parse **parse)
{
	*parse = malloc(sizeof(t_parse));
	if (!(*parse))
		exit(ft_dprintf(2, "Error\nMalloc failed\n"));
	(*parse)->map2d = malloc(sizeof(t_map2d));
	if (!((*parse)->map2d))
		exit(ft_dprintf(2, "Error\nMalloc failed\n"));
	(*parse)->north = NULL;
	(*parse)->south = NULL;
	(*parse)->east = NULL;
	(*parse)->west = NULL;
	(*parse)->ceil_rgb = NULL;
	(*parse)->floor_rgb = NULL;
	(*parse)->map2d->map = NULL;
	(*parse)->map2d->width = 0;
	(*parse)->map2d->height = 0;
	(*parse)->doors = NULL;
	return (1);
}

int	ft_check_content(t_parse *parse)
{
	int	count;

	count = 0;
	if (parse->north)
		count++;
	if (parse->south)
		count++;
	if (parse->east)
		count++;
	if (parse->west)
		count++;
	if (parse->ceil_rgb)
		count++;
	if (parse->floor_rgb)
		count++;
	if (count == 6)
		return (1);
	return (0);
}

int	ft_check_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("012NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_get_map_width(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

t_parse	*parsing(char *file)
{
	t_parse	*parse;
	char	*line;
	int		i;

	if (!ft_init_struct(&parse))
		return (NULL);
	line = ft_parse_map(parse, file);
	if (!line)
		return (NULL);
	parse->map2d->map = ft_parse_map2d(line, parse);
	if (!parse->map2d->map || ft_check_map(parse->map2d->map))
		exit(EXIT_FAILURE);
	parse->map2d->width = ft_get_map_width(parse->map2d->map);
	i = -1;
	while (parse->map2d->map[++i])
		parse->map2d->height++;
	free(line);
	return (parse);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 05:58:09 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/18 13:24:21 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_init_struct(t_parse **parse)
{
	*parse = malloc(sizeof(t_parse));
	if (!(*parse))
		return (0);
	(*parse)->map2d = malloc(sizeof(t_map2d));
	if (!((*parse)->map2d))
		return (free(*parse), 0);
	(*parse)->map1d = malloc(sizeof(t_map1d));
	if (!((*parse)->map1d))
		return (free((*parse)->map2d), free(*parse), 0);
	(*parse)->north = NULL;
	(*parse)->south = NULL;
	(*parse)->east = NULL;
	(*parse)->west = NULL;
	(*parse)->floor = -1;
	(*parse)->ceil = -1;
	(*parse)->map1d->map = NULL;
	(*parse)->map1d->width = 0;
	(*parse)->map1d->height = 0;
	(*parse)->map2d->map = NULL;
	(*parse)->map2d->width = 0;
	(*parse)->map2d->height = 0;
	return (1);
}

int	ft_check_content(t_parse *parse)
{
	int count;

	count = 0;
	if (parse->north)
		count++;
	if (parse->south)
		count++;
	if (parse->east)
		count++;
	if (parse->west)
		count++;
	if (parse->floor != -1)
		count++;
	if (parse->ceil != -1)
		count++;
	if (count == 6)
		return (1);
	return (0);
}

int	ft_is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_is_in_str(" 10NSEWP", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_get_map_width(char *line)
{
	if (line[0])
		return (ft_strlen(line));
	return (0);
}

int	ft_get_map_height(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	ft_create_map1d(t_parse *parse)
{
	int	x;
	int	y;
	int	cur;

	parse->map1d->width = parse->map2d->width;
	parse->map1d->height = parse->map2d->height;
	parse->map1d->map = malloc(sizeof(int) * (parse->map1d->width
				* parse->map1d->height));
	if (!parse->map1d->map)
		return (0);
	y = -1;
	cur = -1;
	while (parse->map2d->map[++y])
	{
		x = -1;
		while (parse->map2d->map[y][++x])
		{
			parse->map1d->map[++cur] = 1;
			if (parse->map2d->map[y][x] == 'P')
				parse->map1d->map[cur] = 2;
			else if (ft_is_in_str("0NSEW", parse->map2d->map[y][x]))
				parse->map1d->map[cur] = 0;
		}
	}
	return (1);
}

t_parse	*parsing(char *file)
{
	t_parse	*parse;
	char	*line;

	if (!ft_init_struct(&parse))
		return (NULL);
	line = ft_parse_map(parse, file);
	if (!line)
		return (NULL);
	parse->map2d->map = ft_parse_map2d(line);
	if (!parse->map2d->map)
		return (free(line), free(parse), NULL);
	parse->map2d->width = ft_get_map_width(line);
	parse->map2d->height = ft_get_map_height(line);
	free(line);
	if (!ft_check_player(parse))
		return (ft_free_parse(parse), NULL);
	if (!ft_create_map1d(parse))
		return (ft_free_parse(parse), NULL);
	if (!ft_check_map(parse))
		return (ft_free_parse(parse), NULL);
	ft_count_player(parse->map2d->map, &(parse->player));
	return (parse);
}

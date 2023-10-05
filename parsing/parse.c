/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 05:58:09 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/05 12:23:34 by abizyane         ###   ########.fr       */
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
	(*parse)->north = NULL;
	(*parse)->south = NULL;
	(*parse)->east = NULL;
	(*parse)->west = NULL;
	(*parse)->floor = -1;
	(*parse)->ceil = -1;
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

int	ft_get_map_width(char **map)
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

int	ft_get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void ft_remove_newlines(t_parse *parse)
{
	int		i;
	char	*temp;

	i = 0;
	while (parse->map2d->map[i])
	{
		temp = ft_substr(parse->map2d->map[i], 0, ft_strlen(parse->map2d->map[i]) - 1);
		temp = ft_strjoin_opt(temp, "\0", 1);
		parse->map2d->map[i] = temp;
		i++;
	}
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
	parse->map2d->map = ft_parse_map2d(line, parse);
	if (!parse->map2d->map)
		exit (EXIT_FAILURE);
	parse->map2d->width = ft_get_map_width(parse->map2d->map);
	parse->map2d->height = ft_get_map_height(parse->map2d->map);
	// ft_remove_newlines(parse);
	free(line);
	// if (!ft_check_player(parse))
	// 	return (ft_free_parse(parse), NULL);
	return (parse);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 05:29:39 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/11 06:10:33 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int ft_get_width(char *line)
{
    int i;
    int current_width;
    int max_width;

    i = 0;
    current_width = 0;
    max_width = 0;
    while (line[i])
    {
        if (line[i] == '\n')
        {
            if (current_width > max_width)
                max_width = current_width;
            current_width = 0;
        }
        else
            current_width++;
        i++;
    }
    return (max_width);
}

static int ft_get_height(char *line)
{
	int i;
	int height;

	i = 0;
	height = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			height++;
		i++;
	}
	return (height);
}

static char **ft_allocation(char *line)
{
	char **map;
	int width;
	int height;
	int i;

	width = ft_get_width(line);
	height = ft_get_height(line);
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(char) * (width + 1));
		if (!map[i])
			return (NULL);
		ft_memset(map[i], ' ', width);
		map[i++][width] = 0;
	}
	map[i] = NULL;
	return (map);
}

char **ft_parse_map2d(char *line)
{
	char **map;
	int i;
	int pos_x;
	int pos_y;

	i = 0;
	pos_x = 0;
	pos_y = 0;
	map = ft_allocation(line);
	if (!map)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\n')
		{
			strlcpy(map[pos_y], line + pos_x, i - pos_x + 1);
			pos_x = i + 1;
		}
		i++;
	}
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 05:29:39 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/05 12:44:35 by abizyane         ###   ########.fr       */
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

int	ft_strlcpy2(char *dst, const char *src, int size)
{
	int	cur;

	if (size == 0)
		return (ft_strlen(src));
	cur = 0;
	while (src[cur] && cur < (size - 1))
	{
		dst[cur] = src[cur];
		cur++;
	}
	return (ft_strlen(src));
}

char **ft_parse_map2d(char *line, t_parse *parse)
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
			ft_strlcpy2(map[pos_y++], line + pos_x, i - pos_x + 1);
			pos_x = i + 1;
			parse->map2d->length = ft_strlen(map[pos_y - 1]);
		}
		i++;
	}
	//TODO: the last line in the map i not loaded
	// int ii = 0;
	// int jj;
	// while (map[ii])
	// {		
	// 	write (1, "\n", 1);
	// 	jj = 0;
	// 	while (map[ii][jj])
	// 		write (1, &map[ii][jj++], 1);
	// 	ii++;
	// }
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 05:58:09 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/09 06:25:09 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int ft_init_struct(t_parse **parse)
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

int ft_check_content(t_parse *parse)
{
    if (parse->north && parse->south &&
        parse->east && parse->west &&
        parse->floor!= -1 &&
        parse->ceil!= -1)
        return 1;
    return 0;
}


t_parse *parsing(char *file)
{
    t_parse *parse;
    char    *line;

    if (!ft_init_struct(&parse))
        return (NULL);
    line = ft_parse_map(parse, file);
    if (!line)
        return (0);
    // parse->map2d->map = ft_parse_map2d(line);
    return (parse);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 04:43:18 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/09 05:05:54 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char *ft_print_error(char *str)
{
    printf("Error\n%s\n", str);
    return (NULL);
}

void ft_free_rgb(char **rgb, char *rgb_str)
{
    int i;

    i = 0;
    while (rgb[i])
    {
        free(rgb[i]);
        i++;
    }
    free(rgb);
    free(rgb_str);
}
void ft_free_parse(t_parse *parse)
{
    if (parse->north)
        free(parse->north);
    if (parse->south)
        free(parse->south);
    if (parse->east)
        free(parse->east);
    if (parse->west)
        free(parse->west);
    if (parse->map1d->map)
        free(parse->map1d->map);
    if (parse->map2d->map)
        free(parse->map2d->map);
    free(parse->map1d);
    free(parse->map2d);
    free(parse);
    // return NULL;
}

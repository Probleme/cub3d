/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 02:14:05 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/12 08:15:52 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int ft_count_player(char **map, t_player *player)
{
    int count;
    int x;
    int y;

    count = 0;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' ||
                map[y][x] == 'E' || map[y][x] == 'W')
            {
                count++;
                *player = (t_player){x, y, map[y][x]};
            }
            x++;
        }
        y++;
    }
    return (count);
}

t_map2d *ft_fill_map2d(t_map2d *map2d)
{
    t_map2d *duplicate;
    int i;

    duplicate = malloc(sizeof(t_map2d));
    if (!map2d)
        return (NULL);
    duplicate->width = map2d->width;
    duplicate->height = map2d->height;
    duplicate->map = malloc(sizeof(char *) * duplicate->height + 1);
    if (!duplicate->map)
        return (free(duplicate), NULL);
    i = 0;
    while (i < duplicate->height)
    {
        duplicate->map[i] = ft_strdup(duplicate->map[i]);
        if (!duplicate->map[i])
            return (free(duplicate->map), free(duplicate), NULL);
        i++;
    }
    duplicate->map[i] = NULL;
    return (duplicate);
}

int ft_check_player(t_parse *parse)
{
    t_map2d *map2d;
    t_player player;
    int count;

    count = ft_count_player(parse->map2d->map, &player);
    if (count == 0)
    {
        printf("Error\n(Map doesn't contain a position for the player)\n");
        return (0);
    }
    else if (count > 1)
    {
        printf("Error\n(Map contains more than one position for the player)\n");
        return (0);
    }
    map2d = ft_fill_map2d(parse->map2d);
    if (!map2d)
        return (0);
    // if (ft_can_exit_map_from_pos(map2d, player.x, player.y))
    // {
    //     printf("Error\n(Map is not closed)\n");
    //     exit(1);
    // }
    // free_map2d(map2d);
    parse->player = player;
    return (1);
}
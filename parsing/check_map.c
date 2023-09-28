/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 04:41:13 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/19 09:34:22 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static char	*static_find_item_front(t_map2d *map2d, int index)
// {
// 	if (index < 0 || index >= map2d->height) {
// 		printf("Index out of range in static_find_item_front\n");
// 		return NULL;
// 	}

// 	return map2d->map[index];
// }

// char	*_ft_list_item_at(t_map2d *map2d, int index)
// {
// 	char *item;

// 	if (!map2d)
// 		return (NULL);

// 	item = static_find_item_front(map2d, index);
// 	if (!item) {
// 		printf("Error in _ft_list_item_at: Item not found\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	return item;
// }


// char	map_get_at(t_map2d *map2d, UINT x, UINT y)
// {
// 	char	*line;

// 	if (y >= (UINT)map2d->height)
// 		return ('\0');
// 	line = _ft_list_item_at(map2d, y);
// 	if (x >= strlen(line))
// 		return ('\0');
// 	return (line[x]);
// }

// bool	is_in_wall_and_set_player(t_cube *cube, t_int_vect pos, char c)
// {
// 	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
// 	{
// 		if (cube->pos_player.x != 0)
// 			exit (printf("Reassigning player position."));
// 		cube->pos_player = (t_float_vect){pos.x + .5, pos.y + .5};
// 		if (c == 'N')
// 			cube->angle += M_PI + M_PI / 2;
// 		else if (c == 'S')
// 			cube->angle += M_PI / 2;
// 		else if (c == 'W')
// 			cube->angle += M_PI;
// 		return (true);
// 	}	
// 	return (c == '0');
// }

// static void	static_test_tile(t_cube *cube, t_int_vect pos)
// {
// 	char	c;

// 	c = map_get_at(cube->parse->map2d, pos.x, pos.y);
// 	if (is_in_wall_and_set_player(cube, pos, c))
// 	{
// 		if (map_get_at(cube->parse->map2d, pos.x + 1, pos.y) == '\n'
// 			|| map_get_at(cube->parse->map2d, pos.x, pos.y + 1) == '\n'
// 			|| map_get_at(cube->parse->map2d, pos.x - 1, pos.y) == '\n'
// 			|| map_get_at(cube->parse->map2d, pos.x, pos.y - 1) == '\n'
// 			|| map_get_at(cube->parse->map2d, pos.x + 1, pos.y) == ' '
// 			|| map_get_at(cube->parse->map2d, pos.x, pos.y + 1) == ' '
// 			|| map_get_at(cube->parse->map2d, pos.x - 1, pos.y) == ' '
// 			|| map_get_at(cube->parse->map2d, pos.x, pos.y - 1) == ' ')
// 			exit (printf("Invalid map.\n"));
// 	}
// 	else if (c == ' ' && c == '1')
// 		exit (printf("Invalid map."));
// }

void	validate_map(t_cube *cube)
{
	// t_int_vect	pos;

	// pos.y = 0;
	// while (pos.y < cube->parse->map2d->height - 1)
	// {
	// 	char *line = _ft_list_item_at(cube->parse->map2d, pos.y);
	// 	if (line == NULL || line[1] == '\0')
	// 		exit (printf("Invalid map.\n"));
	// 	pos.x = 0;
	// 	while ((UINT)pos.x < strlen(line))
	// 	{
	// 		static_test_tile(cube, pos);
	// 		pos.x++;
	// 	}
	// 	pos.y++;
	// }
	// if (cube->pos_player.x == 0)
	// 	exit (printf("Invalid map.\n"));
}

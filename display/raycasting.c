/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:26 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/20 12:07:56 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	is_wall(char c)
{
	if (c == '1' || c == 'D' || c == 'M')
		return (1);
	return (0);
}

char	map_get_at(t_map2d *map, int x, int y)
{
	int	map_y;
	int	map_x;

	map_y = -1;
	map_x = -1;
	if (y >= (int)map->length || x >= (int)map->length)
		return ('\0');
	while (map->map[++map_y])
	{
		map_x = -1;
		while (map->map[map_y][++map_x])
		{
			if (map_y == y && map_x == x)
				return (map->map[map_y][map_x]);
		}
	}
	return ('\0');
}

char	determine_wall_face(float ray_angle)
{
	ray_angle = fmodf(ray_angle, 2.0 * M_PI);
	if (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
		return ('w');
	else if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2)
		return ('e');
	else if (ray_angle == M_PI_2)
		return ('n');
	else
		return ('s');
}   

void	ft_cast_rays(void *param)
{
	t_cube	*cube;
	int		i;
    int		j;
	float	ray_angle;
	float	sin_ray_angle;
	float	cos_ray_angle;
	float	x;
	float	y;

	cube = (t_cube *)param;
    i = -1;
    j = -1;
	while (++i < WIDTH)
	{
		ray_angle = cube->angle + atan2f(i - WIDTH / 2, WIDTH / 2);
		sin_ray_angle = sinf(ray_angle);
		cos_ray_angle = cosf(ray_angle);
		x = cube->pos_player.x;
		y = cube->pos_player.y;
		while (++j < cube->ray_depth)
		{
			x += cos_ray_angle;
			y += sin_ray_angle;
			if (is_wall(map_get_at(cube->parse->map2d, (int)x, (int)y)))
			{
				cube->rays[i].length = sqrtf(powf(x - cube->pos_player.x, 2)
						+ powf(y - cube->pos_player.y, 2));
				cube->rays[i].wall_hit_pos = (t_int_vect){(int)x, (int)y};
				cube->rays[i].wall_face = determine_wall_face(ray_angle);
				break ;
			}
		}
	}
}

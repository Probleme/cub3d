/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:26 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/21 10:24:36 by ataouaf          ###   ########.fr       */
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
	if (y >= (int)map->length)
		return ('\0');
	while (map->map[++map_y])
	{
		map_x = -1;
		while (map->map[map_y][++map_x])
		{
			if (map_y == y)
				return (map->map[map_y][map_x]);
		}
	}
	if (x >= (int)map->length)
		return ('\0');
	return ('\0');
}

t_raycast static_ray_with_face_hit(t_raycast ray, t_int_vect dir, char func)
{
	if (func == 'x')
	{
		if (dir.x == 1)
		{
			ray.wall_face = 'w';
			ray.pos_on_wall = ray.hit_pos.y - (int)ray.hit_pos.y;
		} else
		{
			ray.wall_face = 'e';
			ray.pos_on_wall = 1 - (ray.hit_pos.y - (int)ray.hit_pos.y);
		}
	}
	else
	{
		if (dir.y == 1)
		{
			ray.wall_face = 'n';
			ray.pos_on_wall = 1 - (ray.hit_pos.x - (int)ray.hit_pos.x);
		}
		else
		{
			ray.wall_face = 's';
			ray.pos_on_wall = ray.hit_pos.x - (int)ray.hit_pos.x;
		}
	}
	return ray;
}

static t_raycast static_ray_x(t_cube *cube, float tan_res, t_int_vect dir, t_float_vect pos)
{
	t_raycast ray;
	int i;
	int cor;

	cor = dir.x == -1;
	ray.hit_pos.x = (int)pos.x + dir.x + cor;
	ray.hit_pos.y = (float)(pos.x - (int)pos.x);
	if (dir.x == 1)
		ray.hit_pos.y = 1 - ray.hit_pos.y;
	ray.hit_pos.y = pos.y + (ray.hit_pos.y * tan_res * dir.x);
	i = 0;
	ray.wall_type = is_wall(map_get_at(cube->parse->map2d, ray.hit_pos.x - cor, ray.hit_pos.y));
	while (i < cube->ray_depth && (ray.hit_pos.y < 0 || !ray.wall_type))
	{
		ray.hit_pos.x += dir.x;
		ray.hit_pos.y += (tan_res * dir.x);
		ray.wall_type = is_wall(map_get_at(cube->parse->map2d, ray.hit_pos.x - cor, ray.hit_pos.y));
		i++;
	}
	ray.length = sqrtf(powf(pos.x - ray.hit_pos.x, 2) + powf(pos.y - ray.hit_pos.y, 2));
	ray.wall_hit_pos = (t_int_vect){ray.hit_pos.x - cor, ray.hit_pos.y};
	return static_ray_with_face_hit(ray, dir, 'x');
}

static t_raycast static_ray_y(t_cube *cube, float tan_res, t_int_vect dir, t_float_vect pos)
{
	t_raycast ray;
	int i;
	int cor;

	cor = dir.y == -1;
	ray.hit_pos.y = (int)pos.y + dir.y + cor;
	ray.hit_pos.x = pos.y - (int)pos.y;
	if (dir.y == 1)
		ray.hit_pos.x = 1 - ray.hit_pos.x;
	ray.hit_pos.x = pos.x + ray.hit_pos.x * tan_res * (-dir.y);
	i = 0;
	ray.wall_type = is_wall(map_get_at(cube->parse->map2d, ray.hit_pos.x, ray.hit_pos.y - cor));
	while (i < cube->ray_depth && (ray.hit_pos.x < 0 || !ray.wall_type))
	{
		ray.hit_pos.y += dir.y;
		ray.hit_pos.x += (tan_res * (-dir.y));
		ray.wall_type = is_wall(map_get_at(cube->parse->map2d, ray.hit_pos.x, ray.hit_pos.y - cor));
		i++;
	}
	ray.length = sqrtf(powf(pos.x - ray.hit_pos.x, 2) + powf(pos.y - ray.hit_pos.y, 2));
	ray.wall_hit_pos = (t_int_vect){ray.hit_pos.x, ray.hit_pos.y - cor};
	return static_ray_with_face_hit(ray, dir, 'y');
}

static t_raycast static_cast_ray(t_cube *cube, float r_angle, t_float_vect pos)
{
	t_raycast rays[2];
	t_int_vect dir;

	r_angle = fmodf(r_angle, 2.0 * M_PI);
	if (r_angle < M_PI)
		dir.y = 1;
	else
		dir.y = -1;
	if (r_angle < M_PI_2 || r_angle > M_PI_2 * 3)
		dir.x = 1;
	else
		dir.x = -1;
	rays[0] = static_ray_x(cube, tanf(r_angle), dir, pos);
	rays[1] = static_ray_y(cube, tanf(r_angle + M_PI_2), dir, pos);
	if (rays[0].length > rays[1].length)
		rays[0] = rays[1];
	rays[0].eye_length = rays[0].length	 * cosf(cube->angle - r_angle);
	if (!rays[0].wall_type)
		rays[0].wall_face = '0';
	return rays[0];
}

float ray_angle_fix(t_cube *cube, int i)
{
	float screen_halflen;
	float seg_len;

	screen_halflen = tanf(cube->fov / 2);
	seg_len = screen_halflen / (WIDTH / 2);
	return (atanf(seg_len * i - screen_halflen));
}

void ft_cast_rays(void* param)
{
	t_cube *cube = (t_cube *)param;
	int i = -1;

	while (++i < WIDTH )
	{
		float angle =  cube->angle + ray_angle_fix(cube, i);
		cube->rays[i] = static_cast_ray(cube, angle, cube->pos_player);
	}
}

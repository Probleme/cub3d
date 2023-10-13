/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:46:08 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/12 23:06:48 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check_is_wall(t_map2d *map, double x, double y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x / TILE_SIZE >= map->width || y < 0 || y
		/ TILE_SIZE >= map->height)
		return (0);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (map->map[map_grid_index_y][map_grid_index_x] == '2')
		return (2);
	if (map->map[map_grid_index_y][map_grid_index_x] == '1')
		return (1);
	return (0);
}

void	ft_horizontal_ray(t_cube *cube, t_raycast *ray, t_vect *intercept)
{
	intercept->y = floor(cube->player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->ray_facing_up)
		intercept->y += TILE_SIZE;
	intercept->x = cube->player.pos.x + (intercept->y - cube->player.pos.y)
		/ tan(ray->ray_angle);
	ray->horizontal_step.y = TILE_SIZE;
	if (ray->ray_facing_up)
		ray->horizontal_step.y *= -1;
	ray->horizontal_step.x = TILE_SIZE / tan(ray->ray_angle);
	if ((!ray->ray_facing_right && ray->horizontal_step.x > 0)
		|| (ray->ray_facing_right && ray->horizontal_step.x < 0))
		ray->horizontal_step.x *= -1;
}

void	ft_find_horizontal_wall(t_cube *cube, t_raycast *ray)
{
	t_vect	intercept;
	double	check;

	ft_horizontal_ray(cube, ray, &intercept);
	while (intercept.x >= 0 && intercept.x <= cube->parse->map2d->width
		* TILE_SIZE && intercept.y >= 0
		&& intercept.y <= cube->parse->map2d->height * TILE_SIZE)
	{
		check = intercept.y;
		if (ray->ray_facing_up)
			check--;
		if (ft_check_is_wall(cube->parse->map2d, intercept.x, check) != 0)
		{
			ray->hit_horizontal = 1;
			ray->horizontal_wall_hit.x = intercept.x;
			ray->horizontal_wall_hit.y = intercept.y;
			return ;
		}
		intercept.x += ray->horizontal_step.x;
		intercept.y += ray->horizontal_step.y;
	}
	ray->hit_horizontal = 0;
}

void	ft_vertical_wall(t_cube *cube, t_raycast *ray, t_vect *intercept)
{
	intercept->x = floor(cube->player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_right)
		intercept->x += TILE_SIZE;
	intercept->y = cube->player.pos.y + (intercept->x - cube->player.pos.x)
		* tan(ray->ray_angle);
	ray->vertical_step.x = TILE_SIZE;
	if (!ray->ray_facing_right)
		ray->vertical_step.x *= -1;
	ray->vertical_step.y = TILE_SIZE * tan(ray->ray_angle);
	if ((ray->ray_facing_up && ray->vertical_step.y > 0) || (!ray->ray_facing_up
			&& ray->vertical_step.y < 0))
		ray->vertical_step.y *= -1;
}

void	ft_find_vertical_wall(t_cube *cube, t_raycast *ray)
{
	t_vect	intercept;
	double	check;

	ft_vertical_wall(cube, ray, &intercept);
	while (intercept.x >= 0 && intercept.x <= cube->parse->map2d->width
		* TILE_SIZE && intercept.y >= 0
		&& intercept.y <= cube->parse->map2d->height * TILE_SIZE)
	{
		check = intercept.x;
		if (!ray->ray_facing_right)
			check--;
		if (ft_check_is_wall(cube->parse->map2d, check, intercept.y) != 0)
		{
			ray->hit_vertical = 1;
			ray->vertical_wall_hit.x = intercept.x;
			ray->vertical_wall_hit.y = intercept.y;
			return ;
		}
		intercept.x += ray->vertical_step.x;
		intercept.y += ray->vertical_step.y;
	}
	ray->hit_vertical = 0;
}

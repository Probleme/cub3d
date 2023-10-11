/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:26 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/10 21:09:32 by abizyane         ###   ########.fr       */
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
		return 2;
	if (map->map[map_grid_index_y][map_grid_index_x] == '1')
		return 1;
	return (0);
}

int	ft_is_in_range(t_vect intercept, t_map2d *map)
{
	if (intercept.x >= 0 && intercept.x <= map->width * TILE_SIZE
		&& intercept.y >= 0 && intercept.y <= map->height * TILE_SIZE)
		return (1);
	return (0);
}

void	ft_find_horizontal_wall(t_cube *cube, t_raycast *ray)
{
	t_vect	intercept;
	double	check;

	intercept.y = floor(cube->player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->ray_facing_up)
		intercept.y += TILE_SIZE;
	intercept.x = cube->player.pos.x + (intercept.y - cube->player.pos.y)
		/ tan(ray->ray_angle);
	ray->horizontal_step.y = TILE_SIZE;
	if (ray->ray_facing_up)
		ray->horizontal_step.y *= -1;
	ray->horizontal_step.x = TILE_SIZE / tan(ray->ray_angle);
	if ((!ray->ray_facing_right && ray->horizontal_step.x > 0)
		|| (ray->ray_facing_right && ray->horizontal_step.x < 0))
		ray->horizontal_step.x *= -1;
	while (ft_is_in_range(intercept, cube->parse->map2d))
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

void	ft_find_vertical_wall(t_cube *cube, t_raycast *ray)
{
	t_vect	intercept;
	double	check;

	intercept.x = floor(cube->player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_right)
		intercept.x += TILE_SIZE;
	intercept.y = cube->player.pos.y + (intercept.x - cube->player.pos.x)
		* tan(ray->ray_angle);
	ray->vertical_step.x = TILE_SIZE;
	if (!ray->ray_facing_right)
		ray->vertical_step.x *= -1;
	ray->vertical_step.y = TILE_SIZE * tan(ray->ray_angle);
	if ((ray->ray_facing_up && ray->vertical_step.y > 0) || (!ray->ray_facing_up
			&& ray->vertical_step.y < 0))
		ray->vertical_step.y *= -1;
	while (ft_is_in_range(intercept, cube->parse->map2d))
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

double ft_distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void ft_get_distance_to_wall(t_raycast *rays, t_vect player_pos)
{
	double horizontal_distance = MAXFLOAT;
	double vertical_distance = MAXFLOAT;

	if (rays->hit_horizontal)
		horizontal_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->horizontal_wall_hit.x, rays->horizontal_wall_hit.y);
	if (rays->hit_vertical)
		vertical_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->vertical_wall_hit.x, rays->vertical_wall_hit.y);
	if (horizontal_distance > vertical_distance)
	{
		rays->distance = vertical_distance;
		rays->hit_horizontal = 0;
	}
	else
	{
		rays->distance = horizontal_distance;
		rays->hit_vertical = 0;
	}
}

void	ft_hit_wall_direction(t_raycast *ray, t_cube *cube)
{
	if (ray->hit_horizontal)
	{
		if (ray->ray_facing_up)
		{
			if (ft_check_is_wall(cube->parse->map2d, ray->horizontal_wall_hit.x, ray->horizontal_wall_hit.y - 1. / TILE_SIZE) == 2)
				ray->wall_direction = DOOR;
			else
				ray->wall_direction = NORTH;
		}
		else
		{
			if (ft_check_is_wall(cube->parse->map2d, ray->horizontal_wall_hit.x, ray->horizontal_wall_hit.y + 1. / TILE_SIZE) == 2)
				ray->wall_direction = DOOR;
			else
				ray->wall_direction = SOUTH;
		}
		return ;
	}
	if (ray->ray_facing_right)
	{
		if (ft_check_is_wall(cube->parse->map2d, ray->vertical_wall_hit.x + 1. / TILE_SIZE, ray->vertical_wall_hit.y) == 2)
			ray->wall_direction = DOOR;
		else
			ray->wall_direction = EAST;
	}
	else
	{
		if (ft_check_is_wall(cube->parse->map2d, ray->vertical_wall_hit.x - 1. / TILE_SIZE, ray->vertical_wall_hit.y) == 2)
			ray->wall_direction = DOOR;
		else
			ray->wall_direction = WEST;
	}
	return ;
}

static void	ft_ray_values(t_cube *cube, t_raycast *ray, double r_angle)
{
	ray->hit_horizontal = 0;
	ray->hit_vertical = 0;
	r_angle = fmodf(r_angle, 2 * M_PI);
	if (r_angle < 0)
		r_angle += (2 * M_PI);
	ray->ray_angle = r_angle;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->ray_facing_up = 0;
	else
		ray->ray_facing_up = 1;
	if (ray->ray_angle < (0.5 * M_PI) || ray->ray_angle > (1.5 * M_PI))
		ray->ray_facing_right = 1;
	else
		ray->ray_facing_right = 0;
	ft_find_horizontal_wall(cube, ray);
	ft_find_vertical_wall(cube, ray);
	ft_get_distance_to_wall(ray, cube->player.pos);
	ray->distance *= cos(ray->ray_angle - cube->player.rotation_angle);
	ft_hit_wall_direction(ray, cube);
}

void	ft_cast_rays(void *param)
{
	t_cube	*cube;
	double	ray_angle;
	int		i;

	cube = (t_cube *)param;
	cube->rays = ft_calloc(WIDTH + 1, sizeof(t_raycast));
	if (!cube->rays)
		exit(printf("Failed to allocate memory for rays"));
	i = -1;
	while (++i < WIDTH)
	{
		ray_angle = (cube->player.rotation_angle - cube->player.fov / 2)
			+ ((double)i / WIDTH) * cube->player.fov;
		ft_ray_values(cube, &cube->rays[i], ray_angle);
	}
	if (cube->mlx.img->walls)
	{
		mlx_delete_image(cube->mlx.mlx, cube->mlx.img->walls);
		cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
		cube->mlx.img->walls->enabled = true;
		if (!cube->mlx.img->walls)
			exit(printf("Failed to create walls image"));
	}
}

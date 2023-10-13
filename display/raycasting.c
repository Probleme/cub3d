/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:26 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/13 17:54:55 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_distance_to_wall(t_raycast *rays, t_vect player_pos)
{
	double	horizontal_distance;
	double	vertical_distance;

	horizontal_distance = MAXFLOAT;
	vertical_distance = MAXFLOAT;
	if (rays->hit_horizontal)
		horizontal_distance = sqrt(pow(rays->horizontal_wall_hit.x
					- player_pos.x, 2) + pow(rays->horizontal_wall_hit.y
					- player_pos.y, 2));
	if (rays->hit_vertical)
		vertical_distance = sqrt(pow(rays->vertical_wall_hit.x - player_pos.x,
					2) + pow(rays->vertical_wall_hit.y - player_pos.y, 2));
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

int	ft_hit_wall_direction2(t_raycast *ray, t_cube *cube)
{
	if (ray->ray_facing_right)
	{
		if (ft_check_is_wall(cube->parse->map2d, ray->vertical_wall_hit.x + 1.
				/ TILE_SIZE, ray->vertical_wall_hit.y) == 2)
			ray->wall_direction = DOOR;
		else
			ray->wall_direction = EAST;
	}
	else
	{
		if (ft_check_is_wall(cube->parse->map2d, ray->vertical_wall_hit.x - 1.
				/ TILE_SIZE, ray->vertical_wall_hit.y) == 2)
			ray->wall_direction = DOOR;
		else
			ray->wall_direction = WEST;
		return (1);
	}
	return (0);
}

int	ft_hit_wall_direction(t_raycast *ray, t_cube *cube)
{
	if (ray->hit_horizontal)
	{
		if (ray->ray_facing_up)
		{
			if (ft_check_is_wall(cube->parse->map2d, ray->horizontal_wall_hit.x,
					ray->horizontal_wall_hit.y - 1. / TILE_SIZE) == 2)
				ray->wall_direction = DOOR;
			else
				ray->wall_direction = NORTH;
		}
		else
		{
			if (ft_check_is_wall(cube->parse->map2d, ray->horizontal_wall_hit.x,
					ray->horizontal_wall_hit.y + 1. / TILE_SIZE) == 2)
				ray->wall_direction = DOOR;
			else
				ray->wall_direction = SOUTH;
		}
		return (1);
	}
	return (ft_hit_wall_direction2(ray, cube));
}

static void	ft_ray_values(t_cube *cube, t_raycast *ray, double r_angle)
{
	ray->hit_horizontal = 0;
	ray->hit_vertical = 0;
	r_angle = fmodf(r_angle, 2 * M_PI);
	if (r_angle < 0)
		r_angle += (2 * M_PI);
	else
		r_angle -= (2 * M_PI) * (r_angle > (2 * M_PI));
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
		exit(ft_dprintf(2, "Failed to allocate memory for rays"));
	i = -1;
	while (++i < WIDTH)
	{
		ray_angle = cube->player.rotation_angle + atan((i - (WIDTH / 2))
				/ cube->player.distance_proj_plane);
		ft_ray_values(cube, &cube->rays[i], ray_angle);
	}
	if (cube->mlx.img->walls)
	{
		mlx_delete_image(cube->mlx.mlx, cube->mlx.img->walls);
		cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
		if (!cube->mlx.img->walls)
			exit(ft_dprintf(2, "Failed to create walls image"));
	}
}

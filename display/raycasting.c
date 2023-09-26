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

static t_raycast ft_ray_values(t_cube *cube, float r_angle)
{
	cube->rays->hit_horizontal = 0;
	cube->rays->hit_vertical = 0;
	cube->angle = fmodf(r_angle, 2 * M_PI);
	if (cube->angle < 0)
		cube->angle += 2 * M_PI;
	if (cube->angle <= 0 || cube->angle >= M_PI)
		cube->rays->ray_facing_up = 1;
	else
		cube->rays->ray_facing_up = 0;
	if (cube->angle < 0.5 * M_PI || cube->angle > 1.5 * M_PI)
		cube->rays->ray_facing_right = 1;
	else
		cube->rays->ray_facing_right = 0;
	// ft_find_horizontal_wall(cube);
	// ft_find_vertical_wall(cube);
	return (*cube->rays);
}

void ft_cast_rays(void* param)
{
	t_cube *cube = (t_cube *)param;
	int i = -1;

	while (++i < WIDTH)
	{
		double angle =  cube->player.rotation_angle + atan((i - cube->num_rays / 2) / cube->distance_proj_plane);
		cube->rays[i] = ft_ray_values(cube, angle);
	}
}

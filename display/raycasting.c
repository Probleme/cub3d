/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:26 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/06 23:48:16 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool is_wall_at_location(t_map2d *map, double x, double y)
{
	int map_grid_index_x;
	int map_grid_index_y;

	if (x < 0 || x / TILE_SIZE >= map->width || y < 0 || y / TILE_SIZE >= map->height)
		return (true);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (map->map[map_grid_index_y][map_grid_index_x] == '1');
}

bool ft_is_intercept_in_range(t_vect intercept, t_cube *cube)
{
	return (intercept.x >= 0 && intercept.x / TILE_SIZE <= cube->parse->map2d->width * TILE_SIZE && intercept.y >= 0 && intercept.y / TILE_SIZE <= cube->parse->map2d->height * TILE_SIZE);
}

void ft_find_horizontal_wall(t_cube *cube, t_raycast *ray)
{
	t_vect intercept;

	intercept.y = floor(cube->player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->ray_facing_up)
		intercept.y += TILE_SIZE;
	intercept.x = cube->player.pos.x + (intercept.y - cube->player.pos.y) / tan(ray->ray_angle);
	ray->horizontal_step.y = TILE_SIZE;
	if (ray->ray_facing_up)
		ray->horizontal_step.y *= -1;
	ray->horizontal_step.x = TILE_SIZE / tan(ray->ray_angle);
	if ((!ray->ray_facing_right && ray->horizontal_step.x > 0) || (ray->ray_facing_right && ray->horizontal_step.x < 0))
		ray->horizontal_step.x *= -1;
	while (ft_is_intercept_in_range(intercept, cube))
	{
		double check = intercept.y;
		if (ray->ray_facing_up)
			check--;
		if (is_wall_at_location(cube->parse->map2d, intercept.x, check))
		{
			ray->hit_horizontal = true;
			ray->horizontal_wall_hit.x = intercept.x;
			ray->horizontal_wall_hit.y = intercept.y;
			return ;
		}
		intercept.x += ray->horizontal_step.x;
		intercept.y += ray->horizontal_step.y;
	}
	ray->hit_horizontal = false;
}

void ft_find_vertical_wall(t_cube *cube, t_raycast *ray)
{
	t_vect intercept;

	intercept.x = floor(cube->player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (!ray->ray_facing_right)
		intercept.x += TILE_SIZE;
	intercept.y = cube->player.pos.y + (intercept.x - cube->player.pos.x) * tan(ray->ray_angle);
	ray->vertical_step.x = TILE_SIZE;
	if (ray->ray_facing_right)
		ray->vertical_step.x *= -1;
	ray->vertical_step.y = TILE_SIZE * tan(ray->ray_angle);
	if ((ray->ray_facing_up && ray->vertical_step.y > 0) || (!ray->ray_facing_up && ray->vertical_step.y < 0))
		ray->vertical_step.y *= -1;
	while (ft_is_intercept_in_range(intercept, cube))
	{
		double check = intercept.x;
		if (ray->ray_facing_right)
			check--;
		if (is_wall_at_location(cube->parse->map2d, check, intercept.y))
		{
			ray->hit_vertical = true;
			ray->vertical_wall_hit.x = intercept.x;
			ray->vertical_wall_hit.y = intercept.y;
			return ;
		}
		intercept.x += ray->vertical_step.x;
		intercept.y += ray->vertical_step.y;
	}
	ray->hit_vertical = false;
}

float ft_distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void ft_get_distance_to_wall(t_raycast *rays, t_vect player_pos, double player_rotation)
{
	double horizontal_distance = MAXFLOAT;
	float vertical_distance = MAXFLOAT;
	if (rays->hit_horizontal)
		horizontal_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->horizontal_wall_hit.x, rays->horizontal_wall_hit.y);
	if (rays->hit_vertical)
		vertical_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->vertical_wall_hit.x, rays->vertical_wall_hit.y);
	if (horizontal_distance > vertical_distance)
	{
		rays->distance = vertical_distance;
		rays->hit_vertical = false;
	}
	else
	{
		rays->distance = horizontal_distance;
		rays->hit_horizontal = false;
	}
	rays->distance *= cos(rays->ray_angle - player_rotation);
}

double ft_normalize_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void ft_hi_wall_direction(t_raycast *ray)
{
	if (ray->hit_horizontal)
	{
		if (ray->ray_facing_up)
			ray->wall_direction = NORTH;
		else
			ray->wall_direction = SOUTH;
		return ;
	}
	if (ray->ray_facing_right)
		ray->wall_direction = EAST;
	else
		ray->wall_direction = WEST;
}

static void ft_ray_values(t_cube *cube, t_raycast *ray, double r_angle)
{
	ray->hit_horizontal = false;
	ray->hit_vertical = false;
	ray->ray_angle = ft_normalize_angle(r_angle);
	ray->ray_facing_up = !(ray->ray_angle > 0 && ray->ray_angle < M_PI);
	ray->ray_facing_right = ray->ray_angle < (0.5 * M_PI) || ray->ray_angle > (1.5 * M_PI);
	ft_find_horizontal_wall(cube, ray);
	ft_find_vertical_wall(cube, ray);
	ft_get_distance_to_wall(ray, cube->player.pos, cube->player.rotation_angle);
	ft_hi_wall_direction(ray);
}

// float ft_get_scale(t_cube *cube)
// {
// 	float new_tilesize;

// 	if (cube->parse->map2d->width > cube->parse->map2d->height)
// 		new_tilesize = (WIDTH * MINI_SCALE) / cube->parse->map2d->width;
// 	else
// 		new_tilesize = (HEIGHT * MINI_SCALE) / cube->parse->map2d->height;
// 	return (new_tilesize / TILE_SIZE);
// }

// void ft_draw_line(mlx_image_t *img, t_cube *cube, float endx, float endy)
// {
// 	float len;
// 	float x_step;
// 	float y_step;
// 	float scale;

// 	scale = ft_get_scale(cube);
// 	len = sqrtf((endx - scale * cube->player.pos.x) * (endx - scale * cube->player.pos.x) + (endy - scale * cube->player.pos.y) * (endy - scale * cube->player.pos.y));
// 	x_step = (endx - scale * cube->player.pos.x) / len;
// 	y_step = (endy - scale * cube->player.pos.y) / len;
// 	while (len > 0)
// 	{
// 		mlx_put_pixel(img, endx, endy, 0x00FF0000);
// 		endx -= x_step;
// 		endy -= y_step;
// 		len--;
// 	}
// }

// void ft_draw_rays(t_cube *cube, t_raycast *rays, float num_rays)
// {
// 	int i;
// 	float scale;

// 	scale = ft_get_scale(cube);
// 	if (cube->mlx.img->rays)
// 	{
// 		mlx_delete_image(cube->mlx.mlx, cube->mlx.img->rays);
// 		cube->mlx.img->rays = mlx_new_image(cube->mlx.mlx, cube->parse->map2d->width * TILE_SIZE * scale, cube->parse->map2d->height * TILE_SIZE * scale);
// 		if (!cube->mlx.img->rays)
// 			exit(printf("Failed to create rays image"));
// 	}
// 	i = -1;
// 	while (++i < num_rays - 1)
// 	{
// 		if (rays[i].hit_horizontal)
// 			ft_draw_line(cube->mlx.img->rays, cube, rays[i].horizontal_wall_hit.x * scale, rays[i].horizontal_wall_hit.y * scale);
// 		else if (rays[i].hit_vertical)
// 			ft_draw_line(cube->mlx.img->rays, cube, rays[i].vertical_wall_hit.x * scale, rays[i].vertical_wall_hit.y * scale);
// 	}
// }

t_raycast *ft_cast_all_rays(t_cube *cube)
{
	int i;
	double ray_angle;
	t_raycast *rays;

	rays = malloc(sizeof(t_raycast) * cube->num_rays + 1);
	if (!rays)
		exit(printf("Failed to allocate memory for rays"));
	i = -1;
	while (++i < cube->num_rays)
	{
		ray_angle = cube->player.rotation_angle + atan((i - cube->num_rays / 2) / cube->distance_proj_plane);
		ft_ray_values(cube, &rays[i], ray_angle);
	}
	return (rays);
}

void ft_render(t_cube *cube)
{
	bool draw_rays;

	draw_rays = true;	
	cube->rays = ft_cast_all_rays(cube);
	if (cube->mlx.img->walls)
	{
		mlx_delete_image(cube->mlx.mlx, cube->mlx.img->walls);
		cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
		if (!cube->mlx.img->walls)
			exit(printf("Failed to create walls image"));
	}
	ft_draw_walls(cube, cube->rays);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->walls, 0, 0);
	mlx_set_instance_depth(cube->mlx.img->walls->instances, 3);
	// if (draw_rays)
	// 	ft_draw_rays(cube, cube->rays, cube->num_rays);
	free(cube->rays);
	cube->rays = NULL;
}

void ft_cast_rays(void* param)
{
	t_cube *cube = (t_cube *)param;
	ft_render(cube);
}

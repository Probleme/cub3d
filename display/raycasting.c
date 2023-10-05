/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:26 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/21 10:24:36 by ataouaf          ###   ########.fr       */
=======
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:02:26 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/05 08:24:47 by abizyane         ###   ########.fr       */
>>>>>>> ca246a9c0555e22559a5a417e874b1675d44c3f7
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

<<<<<<< HEAD
int is_wall_at_location(char **map, float x, float y, t_cube *cube)
{
	int map_index_x;
	int map_index_y;

	if (x < 0 || y < 0 || x >= cube->parse->map2d->width || y >= cube->parse->map2d->height)
		return (1);
	map_index_x = floor(x / TILE_SIZE);
	map_index_y = floor(y / TILE_SIZE);
	return (map[map_index_y][map_index_x] == '1');
}

void ft_find_horizontal_wall(t_cube *cube, t_raycast *ray)
{
	t_float_vect intercept;

	ray->horizontal_step.y = TILE_SIZE;
	if (ray->ray_facing_up)
		ray->horizontal_step.y *= -1;
	ray->horizontal_step.x = TILE_SIZE / tan(cube->angle);
	if ((!ray->ray_facing_right && ray->horizontal_step.x > 0) || (ray->ray_facing_right && ray->horizontal_step.x < 0))
		ray->horizontal_step.x *= -1;
	intercept.y = floor(cube->pos_player.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->ray_facing_up)
		intercept.y += TILE_SIZE;
	intercept.x = cube->pos_player.x + (intercept.y - cube->pos_player.y) / tan(cube->angle);
	while (intercept.x >= 0 && intercept.x <= WIDTH && intercept.y >= 0 && intercept.y <= HEIGHT)
	{
		float check = intercept.y;
		if (ray->ray_facing_up)
			check--;
		if (is_wall_at_location(cube->parse->map2d->map, intercept.x, check, cube))
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

void ft_find_vertical_wall(t_cube *cube, t_raycast *ray)
{
	t_float_vect intercept;

	ray->vertical_step.x = TILE_SIZE;
	if (ray->ray_facing_right)
		ray->vertical_step.x *= -1;
	ray->vertical_step.y = TILE_SIZE * tan(cube->angle);
	if ((!ray->ray_facing_up && ray->vertical_step.y > 0) || (ray->ray_facing_up && ray->vertical_step.y < 0))
		ray->vertical_step.y *= -1;
	intercept.x = floor(cube->pos_player.x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_right)
		intercept.x += TILE_SIZE;
	intercept.y = cube->pos_player.y + (intercept.x - cube->pos_player.x) * tan(cube->angle);
	while (intercept.x >= 0 && intercept.x <= WIDTH && intercept.y >= 0 && intercept.y <= HEIGHT)
	{
		float check = intercept.x;
		if (ray->ray_facing_right)
			check--;
		if (is_wall_at_location(cube->parse->map2d->map, check, intercept.y, cube))
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

float ft_distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void ft_get_distance_to_wall(t_raycast *rays, t_float_vect player_pos)
{
	float horizontal_distance;
	float vertical_distance;
	if (rays->hit_horizontal)
		horizontal_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->horizontal_wall_hit.x, rays->horizontal_wall_hit.y);
	if (rays->hit_vertical)
		vertical_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->vertical_wall_hit.x, rays->vertical_wall_hit.y);
	if (horizontal_distance > vertical_distance)
	{
		rays->distance = horizontal_distance;
		rays->hit_vertical = 0;
	}
	else
	{
		rays->distance = vertical_distance;
		rays->hit_horizontal = 0;
	}
	if (rays->hit_vertical)
	{
		if (rays->ray_facing_right)
			rays->wall_direction = EAST;
		else
			rays->wall_direction = WEST;
	}
	else if (rays->hit_horizontal)
	{
		if (rays->ray_facing_up)
			rays->wall_direction = NORTH;
		else
			rays->wall_direction = SOUTH;
	}
}

static t_raycast ft_ray_values(t_cube *cube, float r_angle)
{
	t_raycast ray;

	ray.hit_horizontal = 0;
	ray.hit_vertical = 0;
	cube->angle = fmodf(r_angle, 2 * M_PI);
	if (cube->angle < 0)
		cube->angle += 2 * M_PI;
	if (cube->angle > 0 || cube->angle < M_PI)
		ray.ray_facing_up = 0;
	else
		ray.ray_facing_up = 1;
	if (cube->angle < 0.5 * M_PI || cube->angle > 1.5 * M_PI)
		ray.ray_facing_right = 1;
	else
		ray.ray_facing_right = 0;
	ft_find_horizontal_wall(cube, &ray);
	ft_find_vertical_wall(cube, &ray);
	ft_get_distance_to_wall(&ray, cube->pos_player);
	ray.distance *= cos(cube->angle - cube->player.rotation_angle);
	return (ray);
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
// 	while (++i < num_rays)
// 	{
// 		if (rays[i].hit_horizontal)
// 			ft_draw_line(cube->mlx.img->rays, cube, rays[i].horizontal_wall_hit.x * scale, rays[i].horizontal_wall_hit.y * scale);
// 		else if (rays[i].hit_vertical)
// 			ft_draw_line(cube->mlx.img->rays, cube, rays[i].vertical_wall_hit.x * scale, rays[i].vertical_wall_hit.y * scale);
// 	}
// }

void ft_cast_rays(void* param)
{
	t_cube *cube = (t_cube *)param;
	int i = -1;
	t_raycast *rays;
	// int draw_rays;

	// draw_rays = 1;	
	rays = malloc(sizeof(t_raycast) * cube->num_rays + 1);
	if (!rays)
		exit(printf("Malloc failed"));
	while (++i < WIDTH)
	{
		double angle =  cube->player.rotation_angle + atan((i - cube->num_rays / 2) / cube->distance_proj_plane);
		rays[i] = ft_ray_values(cube, angle);
	}
	cube->rays = rays;
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
	// if (draw_rays == 1)
	// 	ft_draw_rays(cube, cube->rays, cube->num_rays);
	free(cube->rays);
	cube->rays = NULL;
}
=======
// int is_wall_at_location(char **map, float x, float y, t_cube *cube)
// {
// 	int map_index_x;
// 	int map_index_y;

// 	if (x < 0 || y < 0 || x >= cube->parse->map2d->width || y >= cube->parse->map2d->height)
// 		return (1);
// 	map_index_x = floor(x / TILE_SIZE);
// 	map_index_y = floor(y / TILE_SIZE);
// 	return (map[map_index_y][map_index_x] == '1');
// }

// void ft_find_horizontal_wall(t_cube *cube, t_raycast *ray)
// {
// 	t_float_vect intercept;

// 	ray->horizontal_step.y = TILE_SIZE;
// 	if (ray->ray_facing_up)
// 		ray->horizontal_step.y *= -1;
// 	ray->horizontal_step.x = TILE_SIZE / tan(cube->angle);
// 	if ((!ray->ray_facing_right && ray->horizontal_step.x > 0) || (ray->ray_facing_right && ray->horizontal_step.x < 0))
// 		ray->horizontal_step.x *= -1;
// 	intercept.y = floor(cube->pos_player.y / TILE_SIZE) * TILE_SIZE;
// 	if (!ray->ray_facing_up)
// 		intercept.y += TILE_SIZE;
// 	intercept.x = cube->pos_player.x + (intercept.y - cube->pos_player.y) / tan(cube->angle);
// 	while (intercept.x >= 0 && intercept.x <= WIDTH && intercept.y >= 0 && intercept.y <= HEIGHT)
// 	{
// 		float check = intercept.y;
// 		if (ray->ray_facing_up)
// 			check--;
// 		if (is_wall_at_location(cube->parse->map2d->map, intercept.x, check, cube))
// 		{
// 			ray->hit_horizontal = 1;
// 			ray->horizontal_wall_hit.x = intercept.x;
// 			ray->horizontal_wall_hit.y = intercept.y;
// 			return ;
// 		}
// 		intercept.x += ray->horizontal_step.x;
// 		intercept.y += ray->horizontal_step.y;
// 	}
// 	ray->hit_horizontal = 0;
// }

// void ft_find_vertical_wall(t_cube *cube, t_raycast *ray)
// {
// 	t_float_vect intercept;

// 	ray->vertical_step.x = TILE_SIZE;
// 	if (ray->ray_facing_right)
// 		ray->vertical_step.x *= -1;
// 	ray->vertical_step.y = TILE_SIZE * tan(cube->angle);
// 	if ((!ray->ray_facing_up && ray->vertical_step.y > 0) || (ray->ray_facing_up && ray->vertical_step.y < 0))
// 		ray->vertical_step.y *= -1;
// 	intercept.x = floor(cube->pos_player.x / TILE_SIZE) * TILE_SIZE;
// 	if (ray->ray_facing_right)
// 		intercept.x += TILE_SIZE;
// 	intercept.y = cube->pos_player.y + (intercept.x - cube->pos_player.x) * tan(cube->angle);
// 	while (intercept.x >= 0 && intercept.x <= WIDTH && intercept.y >= 0 && intercept.y <= HEIGHT)
// 	{
// 		float check = intercept.x;
// 		if (ray->ray_facing_right)
// 			check--;
// 		if (is_wall_at_location(cube->parse->map2d->map, check, intercept.y, cube))
// 		{
// 			ray->hit_vertical = 1;
// 			ray->vertical_wall_hit.x = intercept.x;
// 			ray->vertical_wall_hit.y = intercept.y;
// 			return ;
// 		}
// 		intercept.x += ray->vertical_step.x;
// 		intercept.y += ray->vertical_step.y;
// 	}
// 	ray->hit_vertical = 0;
// }

// float ft_distance_between_points(float x1, float y1, float x2, float y2)
// {
// 	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
// }

// void ft_get_distance_to_wall(t_raycast *rays, t_float_vect player_pos)
// {
// 	float horizontal_distance = 0;
// 	float vertical_distance = 0;
// 	if (rays->hit_horizontal)
// 		horizontal_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->horizontal_wall_hit.x, rays->horizontal_wall_hit.y);
// 	if (rays->hit_vertical)
// 		vertical_distance = ft_distance_between_points(player_pos.x, player_pos.y, rays->vertical_wall_hit.x, rays->vertical_wall_hit.y);
// 	if (horizontal_distance > vertical_distance)
// 	{
// 		rays->distance = horizontal_distance;
// 		rays->hit_vertical = 0;
// 	}
// 	else
// 	{
// 		rays->distance = vertical_distance;
// 		rays->hit_horizontal = 0;
// 	}
// 	if (rays->hit_vertical)
// 	{
// 		if (rays->ray_facing_right)
// 			rays->wall_direction = EAST;
// 		else
// 			rays->wall_direction = WEST;
// 	}
// 	else if (rays->hit_horizontal)
// 	{
// 		if (rays->ray_facing_up)
// 			rays->wall_direction = NORTH;
// 		else
// 			rays->wall_direction = SOUTH;
// 	}
// }

// static t_raycast ft_ray_values(t_cube *cube, float r_angle)
// {
// 	t_raycast ray;

// 	ray.hit_horizontal = 0;
// 	ray.hit_vertical = 0;
// 	cube->angle = fmodf(r_angle, 2 * M_PI);
// 	if (cube->angle < 0)
// 		cube->angle += 2 * M_PI;
// 	if (cube->angle > 0 || cube->angle < M_PI)
// 		ray.ray_facing_up = 0;
// 	else
// 		ray.ray_facing_up = 1;
// 	if (cube->angle < 0.5 * M_PI || cube->angle > 1.5 * M_PI)
// 		ray.ray_facing_right = 1;
// 	else
// 		ray.ray_facing_right = 0;
// 	ft_find_horizontal_wall(cube, &ray);
// 	ft_find_vertical_wall(cube, &ray);
// 	ft_get_distance_to_wall(&ray, cube->pos_player);
// 	ray.distance *= cos(cube->angle - cube->player.rotation_angle);
// 	return (ray);
// }

// // float ft_get_scale(t_cube *cube)
// // {
// // 	float new_tilesize;

// // 	if (cube->parse->map2d->width > cube->parse->map2d->height)
// // 		new_tilesize = (WIDTH * MINI_SCALE) / cube->parse->map2d->width;
// // 	else
// // 		new_tilesize = (HEIGHT * MINI_SCALE) / cube->parse->map2d->height;
// // 	return (new_tilesize / TILE_SIZE);
// // }

// // void ft_draw_line(mlx_image_t *img, t_cube *cube, float endx, float endy)
// // {
// // 	float len;
// // 	float x_step;
// // 	float y_step;
// // 	float scale;

// // 	scale = ft_get_scale(cube);
// // 	len = sqrtf((endx - scale * cube->player.pos.x) * (endx - scale * cube->player.pos.x) + (endy - scale * cube->player.pos.y) * (endy - scale * cube->player.pos.y));
// // 	x_step = (endx - scale * cube->player.pos.x) / len;
// // 	y_step = (endy - scale * cube->player.pos.y) / len;
// // 	while (len > 0)
// // 	{
// // 		mlx_put_pixel(img, endx, endy, 0x00FF0000);
// // 		endx -= x_step;
// // 		endy -= y_step;
// // 		len--;
// // 	}
// // }

// // void ft_draw_rays(t_cube *cube, t_raycast *rays, float num_rays)
// // {
// // 	int i;
// // 	float scale;

// // 	scale = ft_get_scale(cube);
// // 	if (cube->mlx.img->rays)
// // 	{
// // 		mlx_delete_image(cube->mlx.mlx, cube->mlx.img->rays);
// // 		cube->mlx.img->rays = mlx_new_image(cube->mlx.mlx, cube->parse->map2d->width * TILE_SIZE * scale, cube->parse->map2d->height * TILE_SIZE * scale);
// // 		if (!cube->mlx.img->rays)
// // 			exit(printf("Failed to create rays image"));
// // 	}
// // 	i = -1;
// // 	while (++i < num_rays)
// // 	{
// // 		if (rays[i].hit_horizontal)
// // 			ft_draw_line(cube->mlx.img->rays, cube, rays[i].horizontal_wall_hit.x * scale, rays[i].horizontal_wall_hit.y * scale);
// // 		else if (rays[i].hit_vertical)
// // 			ft_draw_line(cube->mlx.img->rays, cube, rays[i].vertical_wall_hit.x * scale, rays[i].vertical_wall_hit.y * scale);
// // 	}
// // }

// // void ft_cast_rays(void* param)
// // {
// // 	t_cube *cube = (t_cube *)param;
// // 	int i = -1;
// // 	t_raycast *rays;
// // 	// int draw_rays;

// // 	// draw_rays = 1;	
// // 	rays = malloc(sizeof(t_raycast) * cube->num_rays + 1);
// // 	if (!rays)
// // 		exit(printf("Malloc failed"));
// // 	while (++i < WIDTH)
// // 	{
// // 		double angle =  cube->player.rotation_angle + atan((i - cube->num_rays / 2) / cube->distance_proj_plane);
// // 		rays[i] = ft_ray_values(cube, angle);
// // 	}
// // 	cube->rays = rays;
// // 	if (cube->mlx.img->walls)
// // 	{
// // 		mlx_delete_image(cube->mlx.mlx, cube->mlx.img->walls);
// // 		cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
// // 		if (!cube->mlx.img->walls)
// // 			exit(printf("Failed to create walls image"));
// // 	}
// // 	ft_draw_walls(cube, cube->rays);
// // 	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->walls, 0, 0);
// // 	mlx_set_instance_depth(cube->mlx.img->walls->instances, 3);
// // 	// if (draw_rays == 1)
// // 	// 	ft_draw_rays(cube, cube->rays, cube->num_rays);
// // 	free(cube->rays);
// // 	cube->rays = NULL;
// // }
>>>>>>> ca246a9c0555e22559a5a417e874b1675d44c3f7

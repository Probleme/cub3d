/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 02:01:17 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/13 02:09:49 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_image_t	*ft_draw_background(mlx_t *mlx, t_rgb *color)
{
	mlx_image_t	*img;
	int			col;
	int			x;
	int			y;

	img = mlx_new_image(mlx, WIDTH, HEIGHT / 2);
	if (!img)
		exit(ft_dprintf(2, "Failed to create background image\n"));
	col = ((unsigned int)color->red << 24) | ((unsigned int)color->green << 16)
		| ((unsigned int)color->blue << 8) | 255;
	x = 0;
	while (x < (int)img->height)
	{
		y = 0;
		while (y < (int)img->width)
		{
			mlx_put_pixel(img, y, x, col);
			y++;
		}
		x++;
	}
	return (img);
}

static int	ft_get_texture_pixel_color(mlx_texture_t *texture, t_raycast ray,
		double current_height, int width_pixels)
{
	uint8_t	*pixel;
	int		pixel_texture_location;
	double	height_divided;
	int		height;

	if (ray.wall_height > HEIGHT)
		current_height += (ray.wall_height - HEIGHT) / 2;
	height_divided = texture->height / ray.wall_height;
	height = floor((height_divided * current_height)) * texture->width;
	pixel_texture_location = height;
	pixel_texture_location += width_pixels;
	pixel_texture_location *= texture->bytes_per_pixel;
	pixel = &texture->pixels[pixel_texture_location];
	return ((unsigned int)pixel[0] << 24 | (unsigned int)pixel[1] << 16 
		| (unsigned int)pixel[2] << 8 | (unsigned int)pixel[3]);
}

static void	ft_draw_column(t_cube *cube, t_raycast ray, mlx_texture_t *texture,
		int x)
{
	int		width;
	int		current_height;
	int		color;
	double	width_pixels;

	x = x * WALL_STRIP_WIDTH;
	if (ray.hit_horizontal)
		width_pixels = fmod(ray.horizontal_wall_hit.x, TILE_SIZE) / TILE_SIZE;
	else
		width_pixels = fmod(ray.vertical_wall_hit.y, TILE_SIZE) / TILE_SIZE;
	width_pixels *= texture->width;
	current_height = 0;
	while (ray.draw_start + current_height < ray.draw_end)
	{
		color = ft_get_texture_pixel_color(texture, ray, current_height,
				width_pixels);
		width = -1;
		while (++width < WALL_STRIP_WIDTH)
			mlx_put_pixel(cube->mlx.img->walls, x + width, ray.draw_start
				+ current_height, color);
		current_height++;
	}
}

void	ft_draw_info(t_raycast *rays, double distance_proj_plane)
{
	t_raycast	*ray;
	int			i;

	i = 0;
	while (i < WIDTH)
	{
		ray = &rays[i];
		ray->wall_height = ((double)TILE_SIZE / ray->distance)
			* distance_proj_plane;
		ray->draw_start = (HEIGHT / 2) - (ray->wall_height / 2);
		ray->draw_end = ray->draw_start + ray->wall_height;
		if (ray->wall_height > HEIGHT)
		{
			ray->draw_start = 0;
			ray->draw_end = HEIGHT;
		}
		i++;
	}
}

void	ft_draw_walls(void *param)
{
	t_cube			*cube;
	mlx_texture_t	*texture;
	int				i;

	cube = (t_cube *)param;
	i = -1;
	ft_draw_info(cube->rays, cube->player.distance_proj_plane);
	while (++i < WIDTH)
	{
		if (cube->rays[i].wall_direction == NORTH)
			texture = cube->mlx.img->north;
		else if (cube->rays[i].wall_direction == SOUTH)
			texture = cube->mlx.img->south;
		else if (cube->rays[i].wall_direction == EAST)
			texture = cube->mlx.img->east;
		else if (cube->rays[i].wall_direction == WEST)
			texture = cube->mlx.img->west;
		else if (cube->rays[i].wall_direction == DOOR)
			texture = cube->mlx.img->door;
		ft_draw_column(cube, cube->rays[i], texture, i);
	}
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->walls, 0, 0);
	mlx_set_instance_depth(cube->mlx.img->walls->instances, 2);
	free(cube->rays);
	cube->rays = NULL;
}

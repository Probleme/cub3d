/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:52:48 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/18 07:45:44 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t *get_color(mlx_texture_t *texture)
{
	uint32_t *color;
	uint8_t rgb[4];
	unsigned int position;
	int i;

	i = 0;
	color = malloc(sizeof(uint32_t) * (texture->width + 1)* (texture->height + 1));
	if (!color)
		return (NULL);
	position = 0;
	while (position < texture->width * texture->height * texture->bytes_per_pixel)
	{
		rgb[0] = texture->pixels[position];
		rgb[1] = texture->pixels[position + 1];
		rgb[2] = texture->pixels[position + 2];
		rgb[3] = texture->pixels[position + 3];
		color[i] = ft_pixel(rgb[0], rgb[1], rgb[2], rgb[3]);
		position += texture->bytes_per_pixel;
	}
	return (color);
}

// void load_png_image(t_cube *cube, char *path, int position)
// {
// 	// cube->count_images += 1;
// 	mlx_texture_t *texture;

// 	texture = mlx_load_png(path);
// 	cube->mlx.texture[position].img = mlx_texture_to_image(cube->mlx.mlx, texture);
// 	if (position == 0)
// 	{
// 		cube->mlx.north = get_color(texture);
// 		mlx_image_to_window(cube->mlx.mlx, cube->mlx.texture[position].img, 500, 500);
// 	}
// 	else if (position == 1)
// 	{
// 		cube->mlx.south = get_color(texture);
// 		mlx_image_to_window(cube->mlx.mlx, cube->mlx.texture[position].img, 300, 300);
// 	}
// 	else if (position == 2)
// 	{
// 		cube->mlx.east = get_color(texture);
// 		mlx_image_to_window(cube->mlx.mlx, cube->mlx.texture[position].img, 200, 200);
// 	}
// 	else if (position == 3)
// 	{
// 		cube->mlx.west = get_color(texture);
// 		mlx_image_to_window(cube->mlx.mlx, cube->mlx.texture[position].img, 100, 100);
// 	}
// 	mlx_delete_texture(texture);
// 	cube->mlx.texture[position].img->enabled = 1;
// }

void load_images(t_cube *cube)
{
	cube->mlx.img[0].screen = mlx_new_image(cube->mlx.mlx, 128, 127);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img[0].screen, 0, 0);
	cube->mlx.img[0].screen->enabled = 1;
	// cube->count_images += 1;
	// cube->mlx.img[1].img = mlx_new_image(cube->mlx.mlx, 1920, 1080);
	// mlx_image_to_window(cube->mlx.mlx, cube->mlx.img[1].img, 0, 0);
	// cube->mlx.img[1].img->enabled = 1;
	// cube->count_images += 1;
	// cube->mlx.img[2].img = mlx_new_image(cube->mlx.mlx, 1920, 1080);
	// mlx_image_to_window(cube->mlx.mlx, cube->mlx.img[2].img, 0, 0);
	// cube->mlx.img[2].img->enabled = 1;
	// cube->count_images += 1;
}

void init_images(t_cube *cube)
{
	(void)cube;
	// cube->count_images = 0;
	// load_images(cube);
	// load_png_image(cube, cube->parse->north, 0);
	// load_png_image(cube, cube->parse->south, 1);
	// load_png_image(cube, cube->parse->east, 2);
	// load_png_image(cube, cube->parse->west, 3);
	// load_png_image(cube, "./textures/door.png", 4);
}

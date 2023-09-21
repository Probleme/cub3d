/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:52:48 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/21 06:02:45 by ataouaf          ###   ########.fr       */
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

void load_png_image(t_cube *cube, char *path)
{
	mlx_texture_t *texture;

	texture = mlx_load_png(path);
	if (path == cube->parse->north)
		cube->mlx.img->north = mlx_texture_to_image(cube->mlx.mlx, texture);
	if (path == cube->parse->south)
		cube->mlx.img->south = mlx_texture_to_image(cube->mlx.mlx, texture);
	if (path == cube->parse->east)
		cube->mlx.img->east = mlx_texture_to_image(cube->mlx.mlx, texture);
	if (path == cube->parse->west)
		cube->mlx.img->west = mlx_texture_to_image(cube->mlx.mlx, texture);
	mlx_delete_texture(texture);
}

void ft_load_png(t_cube *cube)
{
	load_png_image(cube, cube->parse->north);
	load_png_image(cube, cube->parse->south);
	load_png_image(cube, cube->parse->east);
	load_png_image(cube, cube->parse->west);
}

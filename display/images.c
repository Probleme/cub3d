/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:52:48 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/21 09:03:57 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void load_png_image(t_cube *cube, char *path)
{
	if (path == cube->parse->north)
		cube->mlx.img->north = mlx_load_png(path);
	else if (path == cube->parse->south)
		cube->mlx.img->south = mlx_load_png(path);
	else if (path == cube->parse->east)
		cube->mlx.img->east = mlx_load_png(path);
	else if (path == cube->parse->west)
		cube->mlx.img->west = mlx_load_png(path);
}

void ft_load_png(t_cube *cube)
{ 
	load_png_image(cube, cube->parse->north);
	load_png_image(cube, cube->parse->east);
	load_png_image(cube, cube->parse->west);
	load_png_image(cube, cube->parse->south);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:52:48 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/07 15:10:04 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_load_png(t_cube *cube)
{ 
	if (cube->parse->north)
		cube->mlx.img->north = mlx_load_png(cube->parse->north);
	if (cube->parse->south)
		cube->mlx.img->south = mlx_load_png(cube->parse->south);
	if (cube->parse->east)
		cube->mlx.img->east = mlx_load_png(cube->parse->east);
	if (cube->parse->west)
		cube->mlx.img->west = mlx_load_png(cube->parse->west);
}

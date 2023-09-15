/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:52:48 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/15 03:53:54 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

u_int32_t	**ft_mem2array(uint32_t *mem, size_t len_x, size_t len_y)
{
	u_int32_t	**arr;
	size_t		i;

	arr = malloc(len_y * sizeof(u_int32_t *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len_y)
	{
		arr[i] = &(mem[i * len_x]);
		++i;
	}
	return (arr);
}

void init_texture(t_cube *cube, int index, int *i)
{
    cube->mlx.texture[index].img = mlx_new_image(cube->mlx.mlx, cube->mlx.texture[index].width, cube->mlx.texture[index].height);
    if (!cube->mlx.texture[index].img)
        return;
    *i += 1;
    cube->mlx.texture[index].arr = ft_mem2array((uint32_t *)cube->mlx.texture[index].addr, cube->mlx.texture[index].width, cube->mlx.texture[index].height);
}

void init_imagesparthree(t_cube *cube, int *i)
{
    init_texture(cube, 2, i);
    init_texture(cube, 3, i);
    init_texture(cube, 4, i);
}

void init_imagesparttwo(t_cube *cube, int *i)
{
    *i += 1;
    cube->mlx.img[2].arr = ft_mem2array((uint32_t *)cube->mlx.img[2].addr, 1920, 1080);
    init_texture(cube, 0, i);
    init_texture(cube, 1, i);
    init_imagesparthree(cube, i);
}

void init_imagespartone(t_cube *cube, int *i)
{
    cube->mlx.img[0].img = mlx_new_image(cube->mlx.mlx, 1920, 1080);
    cube->mlx.img[1].img = mlx_new_image(cube->mlx.mlx, 1920, 1080);
    cube->mlx.img[2].img = mlx_new_image(cube->mlx.mlx, 1920, 1080);
    if (!cube->mlx.img[0].img || !cube->mlx.img[1].img || !cube->mlx.img[2].img)
        return;
    *i += 3;
    cube->mlx.img[0].arr = ft_mem2array((uint32_t *)cube->mlx.img[0].addr, 1920, 1080);
    cube->mlx.img[1].arr = ft_mem2array((uint32_t *)cube->mlx.img[1].addr, 1920, 1080);
    cube->mlx.img[2].arr = ft_mem2array((uint32_t *)cube->mlx.img[2].addr, 1920, 1080);
    init_imagesparttwo(cube, i);
}

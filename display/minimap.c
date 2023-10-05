/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:56:32 by abizyane          #+#    #+#             */
/*   Updated: 2023/10/05 12:04:03 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    ft_draw_minimap(t_cube *cube)
{
    int i;
    int j;
    t_vect idx;
    t_vect start;

    start.y = cube->player.pos.y - (HEIGHT * MINI_SCALE) / 2;
    i = 0;
    while (i < HEIGHT * MINI_SCALE && cube->parse->map2d->map\
        [(int)floor(start.y / TILE_SIZE)])
    {
        j = 0;
        start.x = cube->player.pos.x - (WIDTH * MINI_SCALE) / 2;
        while (j < WIDTH * MINI_SCALE && cube->parse->map2d->map\
            [(int)floor(start.y / TILE_SIZE)][(int)floor(start.x / TILE_SIZE)])
        {
            idx.x = floor(start.x / TILE_SIZE);
            idx.y = floor(start.y / TILE_SIZE);
            if (cube->parse->map2d->map[(int)idx.y][(int)idx.x] == '0')
                mlx_put_pixel(cube->mlx.img->mini_map, j, i, 0x040101FF);
            else
                mlx_put_pixel(cube->mlx.img->mini_map, j, i, 0xD1D1D1FF);
            j++;
            start.x++;
        }
        i++;
        start.y++;
    }
}    //TODO: handle the walls collision and the edges of the map
void    ft_draw_player(t_cube *cube)
{
    t_vect idx;
    t_vect pos;

    pos.x = (WIDTH * MINI_SCALE) / 2;
    pos.y = (HEIGHT * MINI_SCALE) / 2;
    idx.y = pos.y;
    while (idx.y < pos.y + 8 && idx.y < HEIGHT)
    {
        idx.x = pos.x;
        while (idx.x < pos.x + 8 && idx.x < WIDTH)
        {
			mlx_put_pixel(cube->mlx.img->mini_map, idx.x, idx.y, 0xF72200FF);
            idx.x++;
        }
        idx.y++;
    }
}   //TODO: add player field of view
void    ft_minimap(void *param)
{
    t_cube *cube;
    
    cube = (t_cube *)param;
    cube->mlx.img->mini_map = mlx_new_image(cube->mlx.mlx,\
        WIDTH * MINI_SCALE, HEIGHT * MINI_SCALE);
    ft_draw_minimap(cube);
    ft_draw_player(cube);
    //TODO: add minimap borders frame
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->mini_map, 20, 10);
    
}
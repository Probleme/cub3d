/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:56:38 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/30 14:53:47 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_player_rotation(t_cube *cube)
{
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_LEFT))
    {
        cube->angle -= .05;
        if (cube->angle < 2.0 * M_PI)
            cube->angle += 2.0 * M_PI;
    }
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_RIGHT))
    {
        cube->angle += .05;
        if (cube->angle >= 4.0 * M_PI)
            cube->angle -= 2.0 * M_PI;
    }
}
// ana kanched liha l3barat moraha ghanormalizi hadchi , rah ban liya lblan daba
void ft_player_movement(void *param)
{
    t_cube *cube = (t_cube *)param;
    t_float_vect new_pos;
    float angle;

    
    ft_player_rotation(cube);
    new_pos = (t_float_vect){0, 0};
    // if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_ESCAPE))
    //     exit(0);
    int x;
    int y;
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_W))
        
        {
            angle = cube->angle - ( 30  * (M_PI / 180));
            angle = 270  * (M_PI / 180);
            printf("angle = %f\n", angle);
            x = cube->pos_player.x + 1.5 * cosf(angle);
            y = cube->pos_player.y + 1.5 * sinf(angle);
            if (cube->parse->map2d->map[y/64][x/64] != '1')
            {
                cube->pos_player.x = x;
                cube->pos_player.y = y;
            }
        }
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_S))
    {
            angle = cube->angle - ( 210  * (M_PI / 180));
        cube->pos_player.x = cube->pos_player.x + 1.5 * cosf(angle);
    cube->pos_player.y = cube->pos_player.y + 1.5 * sinf(angle);                                
    }
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_A))
        {
            angle = cube->angle - ( 120  * (M_PI / 180));
        cube->pos_player.x = cube->pos_player.x + 1.5 * cosf(angle);
    cube->pos_player.y = cube->pos_player.y + 1.5 * sinf(angle);                                
    }
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_D))
    {
            angle = cube->angle + ( 60  * (M_PI / 180));
        cube->pos_player.x = cube->pos_player.x + 1.5 * cosf(angle);
    cube->pos_player.y = cube->pos_player.y + 1.5 * sinf(angle);                                
    }
    // if (!(new_pos.x + 2 * new_pos.y))
    //     return ;
    // angle = atanf(new_pos.y / new_pos.x) + cube->angle;
    // if (new_pos.x < 0)
    //     angle += M_PI;
    // cube->pos_player.x = cube->pos_player.x + 1.5 * cosf(cube->angle);
    // cube->pos_player.y = cube->pos_player.y + 1.5 * sinf(cube->angle);
}

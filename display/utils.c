/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:56:38 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/21 10:22:59 by ataouaf          ###   ########.fr       */
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

void ft_player_movement(void *param)
{
    t_cube *cube = (t_cube *)param;
    t_float_vect new_pos;
    float angle;

    ft_player_rotation(cube);
    new_pos = (t_float_vect){0, 0};
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_W))
        new_pos.x++;
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_S))
        new_pos.x--;
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_A))
        new_pos.y--;
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_D))
        new_pos.y++;
    if (!(new_pos.x + 2 * new_pos.y))
        return ;
    angle = atanf(new_pos.y / new_pos.x) + cube->angle;
    if (new_pos.x < 0)
        angle += M_PI;
    cube->pos_player.x = cube->pos_player.x + 0.5 * cosf(angle);
    cube->pos_player.y = cube->pos_player.y + 0.5 * sinf(angle);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:56:38 by ataouaf           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/21 10:22:59 by ataouaf          ###   ########.fr       */
=======
/*   Updated: 2023/10/05 13:54:52 by abizyane         ###   ########.fr       */
>>>>>>> ca246a9c0555e22559a5a417e874b1675d44c3f7
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

<<<<<<< HEAD
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
    if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_ESCAPE))
        exit(0);
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
=======
void player_rotation(t_cube *cube)
{
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_LEFT))
		cube->player.angle -= cube->player.rotation_speed;
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_RIGHT))
		cube->player.angle += cube->player.rotation_speed;
}

void	check_next_tile(t_cube *cube, t_vect direction)
{
	int x;
	int	y;

	x = floor(direction.x/TILE_SIZE);
	y = floor(direction.y/TILE_SIZE);
	if (y > cube->parse->map2d->height || y < 0 || x > cube->parse->map2d->width || x < 0)
		return;
	if (!cube->parse->map2d->map[y][x] || cube->parse->map2d->map[y][x] == '1')
		return;
	cube->player.pos.x = direction.x;
	cube->player.pos.y = direction.y;
	cube->player.turn_dir = 0;
	cube->player.walk_dir = 0;
}

// void	side_movement(t_cube *cube, t_vect direction)
// {
// }

void ft_player_movement(void *param)
{
	t_cube *cube = (t_cube *)param;
	t_vect direction;
	
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_W) || mlx_is_key_down(cube->mlx.mlx, MLX_KEY_S) ||
			mlx_is_key_down(cube->mlx.mlx, MLX_KEY_A) || mlx_is_key_down(cube->mlx.mlx, MLX_KEY_D))
	{
		if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_W))
			cube->player.walk_dir = 1; 
		if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_S))
			cube->player.walk_dir = -1;
		// if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_A))
		// 	cube->player.turn_dir = -1;
		// if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_D))
		// 	cube->player.turn_dir = 1;
		player_rotation(cube);
		float step = cube->player.walk_dir * cube->player.move_speed;
		direction.x = cube->player.pos.x + cosf(cube->player.angle) * step;
		direction.y = cube->player.pos.y + sinf(cube->player.angle) * step;
		check_next_tile(cube, direction);
	}
>>>>>>> ca246a9c0555e22559a5a417e874b1675d44c3f7
}

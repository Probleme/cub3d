/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:56:38 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/05 13:54:52 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
}

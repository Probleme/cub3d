/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:56:38 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/06 11:25:33 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	player_rotation(t_cube *cube)
{
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_LEFT))
		cube->player.angle -= cube->player.rotation_speed;
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_RIGHT))
		cube->player.angle += cube->player.rotation_speed;
}

static void	player_movements(t_cube *cube, t_vect *next_pos, t_vect *speed)
{
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_W))
	{
			next_pos->x += speed->x;
			next_pos->y += speed->y;
	}
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_S))
	{
			next_pos->x -= speed->x; 	
			next_pos->y -= speed->y;
	}
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_A))
	{
			next_pos->x += speed->y;
			next_pos->y -= speed->x;
	}
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_D))
	{
			next_pos->x -= speed->y;	
			next_pos->y += speed->x;
	}
}

// static double	closest_idx(double x)
// {
// 	double lowest;
	
// 	lowest = floor(x);
// 	if (x - lowest > .5 )
// 		return (lowest + 1);
// 	else
// 		return (lowest);
// }

static int	check_next_tile(t_cube *cube, double next_x, double next_y)
{
	int x;
	int	y;

	x = (int)floor(next_x / TILE_SIZE);
	y = (int)floor(next_y / TILE_SIZE);
	if (y > cube->parse->map2d->height || y < 0 || x > cube->parse->map2d->width || x < 0)
		return 1;
	if (!cube->parse->map2d->map[y][x] || cube->parse->map2d->map[y][x] == '1')
		return 1;
	return 0;
}

void ft_player_movement(void *param)
{
	t_cube *cube = (t_cube *)param;
	t_vect	speed;
	t_vect	next_pos;

	speed.x = cosf(cube->player.angle) * cube->player.move_speed;
	speed.y = sinf(cube->player.angle) * cube->player.move_speed;
	next_pos.x = cube->player.pos.x;
	next_pos.y = cube->player.pos.y;
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_ESCAPE))
		exit(0);
	player_movements(cube, &next_pos, &speed);
	player_rotation(cube);
	if (check_next_tile(cube, next_pos.x, next_pos.y) || check_next_tile(cube, next_pos.x + 1, next_pos.y)\
		|| check_next_tile(cube, next_pos.x - 1, next_pos.y) || check_next_tile(cube, next_pos.x, next_pos.y + 1)\
			||check_next_tile(cube, next_pos.x, next_pos.y - 1))
		return;
	cube->player.pos.x = next_pos.x;
	cube->player.pos.y = next_pos.y;
}

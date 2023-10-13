/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:56:38 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/13 13:10:57 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	player_rotation(t_cube *cube)
{
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_LEFT))
		cube->player.rotation_angle -= cube->player.rotation_speed;
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_RIGHT))
		cube->player.rotation_angle += cube->player.rotation_speed;
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

static void	mouse_movement(t_cube *cube)
{
	int		mouse_x;
	int		mouse_y;
	double	angle;

	mlx_get_mouse_pos(cube->mlx.mlx, &mouse_x, &mouse_y);
	mlx_set_mouse_pos(cube->mlx.mlx, WIDTH / 2, HEIGHT / 2);
	if (mouse_x > WIDTH / 2)
	{
		angle = cube->player.rotation_angle + (mouse_x - WIDTH / 2) * 0.01;
		cube->player.rotation_angle = angle;
	}
	else if (mouse_x < WIDTH / 2)
	{
		angle = cube->player.rotation_angle - (WIDTH / 2 - mouse_x) * 0.01;
		cube->player.rotation_angle = angle;
	}
}

static int	check_next_tile(t_cube *cube, double next_x, double next_y)
{
	int	x;
	int	y;

	x = (int)floor(next_x / TILE_SIZE);
	y = (int)floor(next_y / TILE_SIZE);
	if (y > cube->parse->map2d->height || y < 0 || x > cube->parse->map2d->width
		|| x < 0)
		return (1);
	if (!cube->parse->map2d->map[y][x] || cube->parse->map2d->map[y][x] == '1')
		return (1);
	return (0);
}

void	ft_player_movement(void *param)
{
	t_cube	*cube;
	t_vect	speed;
	t_vect	next_pos;

	cube = (t_cube *)param;
	speed.x = cosf(cube->player.rotation_angle) * cube->player.move_speed;
	speed.y = sinf(cube->player.rotation_angle) * cube->player.move_speed;
	next_pos.x = cube->player.pos.x;
	next_pos.y = cube->player.pos.y;
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_ESCAPE))
		exit(0);
	player_movements(cube, &next_pos, &speed);
	player_rotation(cube);
	mouse_movement(cube);
	if (check_next_tile(cube, next_pos.x, next_pos.y) || check_next_tile(cube,
			next_pos.x + 1, next_pos.y) || check_next_tile(cube, next_pos.x - 1,
			next_pos.y) || check_next_tile(cube, next_pos.x, next_pos.y + 1)
		|| check_next_tile(cube, next_pos.x, next_pos.y - 1))
		return ;
	cube->player.pos.x = next_pos.x;
	cube->player.pos.y = next_pos.y;
}

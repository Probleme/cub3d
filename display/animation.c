/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:03:29 by abizyane          #+#    #+#             */
/*   Updated: 2023/10/13 15:14:01 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_rotation_angle(t_cube *cube, char direction)
{
	if (direction == 'N')
		cube->player.rotation_angle = M_PI * 1.5;
	else if (direction == 'E')
		cube->player.rotation_angle = M_PI * 2;
	else if (direction == 'S')
		cube->player.rotation_angle = M_PI * 0.5;
	else if (direction == 'W')
		cube->player.rotation_angle = M_PI;
	else
		exit(ft_dprintf(2, "Failed to set initial player rotation\n"));
	return (1);
}

void	ft_init_player(t_cube *cube)
{
	t_vect	pos;
	char	direction;

	pos.y = -1;
	cube->player.move_speed = 4;
	cube->player.rotation_speed = 4 * (M_PI / 180);
	cube->player.fov = (FOV_ANGLE * (M_PI / 180));
	cube->player.distance_proj_plane = (WIDTH / 2) / tan(cube->player.fov / 2);
	while (cube->parse->map2d->map[(int)++pos.y])
	{
		pos.x = -1;
		while (cube->parse->map2d->map[(int)pos.y][(int)++pos.x])
		{
			if (is_player(cube->parse->map2d->map[(int)pos.y][(int)pos.x]))
			{
				cube->player.pos.x = pos.x * TILE_SIZE + (0.5 * TILE_SIZE);
				cube->player.pos.y = pos.y * TILE_SIZE + (0.5 * TILE_SIZE);
				direction = cube->parse->map2d->map[(int)pos.y][(int)pos.x];
				if (ft_rotation_angle(cube, direction))
					return ;
			}
		}
	}
	exit(ft_dprintf(2, "Failed to set initial player position\n"));
}

void	init_animation(t_cube *cube, int i)
{
	mlx_texture_t	*tmp;

	cube->mlx.img->gun = ft_calloc(1, sizeof(t_image));
	if (!cube->mlx.img->gun)
		exit(ft_dprintf(2, "Failed to allocate memory\n"));
	while (++i < 5)
	{
		cube->mlx.img->gun->shotgun[i] = mlx_new_image(cube->mlx.mlx, 400, 400);
		cube->mlx.img->gun->shotgun[i] = mlx_texture_to_image(cube->mlx.mlx,
				cube->mlx.img->sprite[i]);
		mlx_delete_texture(cube->mlx.img->sprite[i]);
		mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->gun->shotgun[i], WIDTH
			/ 2 - 100, HEIGHT - 175);
		cube->mlx.img->gun->shotgun[i]->enabled = false;
	}
	cube->mlx.img->gun->shotgun[0]->enabled = true;
	tmp = mlx_load_png("textures/target.png");
	cube->mlx.img->target = mlx_texture_to_image(cube->mlx.mlx, tmp);
	mlx_delete_texture(tmp);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->target, WIDTH / 2, HEIGHT
		/ 2);
}

static void	ft_shoot(t_cube *cube)
{
	if (cube->mlx.img->gun->state == 1 && cube->mlx.img->gun->i == 3)
	{
		cube->mlx.img->gun->shotgun[cube->mlx.img->gun->curr]->enabled = false;
		cube->mlx.img->gun->curr++;
		if (cube->mlx.img->gun->curr == 5)
		{
			cube->mlx.img->gun->state = 0;
			cube->mlx.img->gun->curr = 0;
			cube->mlx.img->gun->shotgun[cube->mlx.img->gun->curr]->enabled = 1;
			return ;
		}
		cube->mlx.img->gun->state = 1;
		cube->mlx.img->gun->shotgun[cube->mlx.img->gun->curr]->enabled = true;
		cube->mlx.img->gun->i = 0;
	}
	else if (cube->mlx.img->gun->state != 0)
	{
		cube->mlx.img->gun->i++;
		cube->mlx.img->gun->state = 1;
	}
}

void	ft_animate_sprites(void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	if (cube->mlx.img->gun->state != 1 && (mlx_is_key_down(cube->mlx.mlx,
				MLX_KEY_SPACE) || mlx_is_mouse_down(cube->mlx.mlx,
				MLX_MOUSE_BUTTON_LEFT)))
		cube->mlx.img->gun->state = 1;
	ft_shoot(cube);
}

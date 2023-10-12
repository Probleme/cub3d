/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:03:29 by abizyane          #+#    #+#             */
/*   Updated: 2023/10/12 20:27:30 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_animation(t_cube *cube)
{
		int				i;
		mlx_texture_t	*tmp;

		static char *images[] = {"textures/shotgun1.png",
							"textures/shotgun2.png",
							"textures/shotgun3.png",
							"textures/shotgun4.png",
							"textures/shotgun5.png"};	
		cube->mlx.img->gun = ft_calloc(1, sizeof(t_image));
		i = 0;
		while (i < 5)
		{
			cube->mlx.img->gun->shotgun[i] = mlx_new_image(cube->mlx.mlx, 400, 400);
			tmp = mlx_load_png(images[i]);
			cube->mlx.img->gun->shotgun[i] = mlx_texture_to_image(cube->mlx.mlx, tmp);
			free (tmp);
			mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->gun->shotgun[i], WIDTH / 2 - 100, HEIGHT - 175);
			cube->mlx.img->gun->shotgun[i]->enabled = false;
			i++;
		}
		cube->mlx.img->gun->shotgun[0]->enabled = true;
		tmp = mlx_load_png("textures/target.png");
		cube->mlx.img->target = mlx_texture_to_image(cube->mlx.mlx, tmp);
		free (tmp);
		mlx_image_to_window(cube->mlx.mlx , cube->mlx.img->target, WIDTH / 2 , HEIGHT / 2);
}

void	ft_shoot(t_cube *cube)
{
	if (cube->mlx.img->gun->state == 1 && cube->mlx.img->gun->i == 3)
	{
		cube->mlx.img->gun->shotgun[cube->mlx.img->gun->curr]->enabled = false;
		cube->mlx.img->gun->curr++;
		if (cube->mlx.img->gun->curr == 5)
		{
			cube->mlx.img->gun->state = 0;
			cube->mlx.img->gun->curr = 0;
 			cube->mlx.img->gun->shotgun[cube->mlx.img->gun->curr]->enabled = true;
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
	if (cube->mlx.img->gun->state != 1 && (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_SPACE)\
		|| mlx_is_mouse_down(cube->mlx.mlx, MLX_MOUSE_BUTTON_LEFT)))
			cube->mlx.img->gun->state = 1;
	ft_shoot(cube);
}

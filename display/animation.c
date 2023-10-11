/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:03:29 by abizyane          #+#    #+#             */
/*   Updated: 2023/10/11 17:25:12 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/cub3d.h"

static t_image	*lstnew_image(char *img, t_mlx	ptr)
{
	t_image	*new;

	new = ft_calloc(sizeof(t_image), 1);
	if (!new)
		return (NULL);
	new->shotgun = mlx_new_image(ptr.mlx, 400, 400);
	new->shotgun = mlx_texture_to_image(ptr.mlx, mlx_load_png(img));
	mlx_image_to_window(ptr.mlx, new->shotgun, WIDTH / 2 - 100, HEIGHT - 180);
	new->shotgun->enabled = false;
	new->state = 0;
	new->i = 0;
	new->j = 0;
	new->nxt = NULL;
	return (new);
}

t_image	*last_image(t_image *head)
{
	t_image	*tmp;

	tmp = head;
	if (!head || !tmp->nxt)
		return (head);
	while (tmp && tmp->nxt)
		tmp = tmp->nxt;
	return (tmp);
}

static void	lstadd_image(t_image **head, char *img, t_mlx ptr)
{
	t_image	*new;
	t_image	*tmp;

	new = lstnew_image(img, ptr);
	tmp = *head;
	if (!tmp)
		(*head) = new;
	else
	{
		while (tmp && tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new;
	}
}

void	lstclear_images(t_image **head, t_cube *cube)
{
	t_image	*tmp;
	t_image	*next;

	tmp = (*head);
	while (tmp)
	{
		next = tmp->nxt;
		mlx_delete_image(cube->mlx.mlx, tmp->shotgun);
		free(tmp);
		tmp = next;
	}
}

void	ft_shoot(t_cube *cube, t_image *image)
{
    while(cube->mlx.img->gun)    
	{
		if (image->i == 6)
		{
			cube->mlx.img->gun->shotgun->enabled = false;
			cube->mlx.img->gun = cube->mlx.img->gun->nxt;
			puts("xxxxxxx");
			if (cube->mlx.img->gun)
 				cube->mlx.img->gun->shotgun->enabled = true;
			image->i = 0;
		}
		else
		{
			if (image->j == 20)
			{
				image->i++;
				image->j = 0;
			}
			else
				image->j++;
		}
	}
	image->state = 0;
	cube->mlx.img->gun = image;
	cube->mlx.img->gun->shotgun->enabled = true;
	// int i = 0;
	
	// while (cube->mlx.img->gun)
	// {
	// 	if (i == 0)
 	// 	{
	// 		cube->mlx.img->gun->shotgun->enabled = false;
	// 		cube->mlx.img->gun = cube->mlx.img->gun->nxt;
	// 		if (cube->mlx.img->gun)
 	// 			cube->mlx.img->gun->shotgun->enabled = true;
	// 		i = 500;
	// 		puts("hhhh");
	// 	}
	// 	else
	// 		i--;
	// }

}

void	init_animation(t_cube *cube)
{
		int		i;

		static char *images[] = {"textures/shotgun1.png",
							"textures/shotgun2.png",
							"textures/shotgun3.png",
							"textures/shotgun4.png",
							"textures/shotgun5.png"};	
		cube->mlx.img->gun = NULL;
		i = 0;
		while (i < 5)
			lstadd_image(&cube->mlx.img->gun, images[i++], cube->mlx);
		cube->mlx.img->gun->shotgun->enabled = true;
}

void	ft_animate_sprites(void *param)
{
	static t_image		*image;
	t_cube	*cube;

	cube = (t_cube *)param;
	image = cube->mlx.img->gun;
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_SPACE) ||
			mlx_is_mouse_down(cube->mlx.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		puts("hhh");
		cube->mlx.img->gun->state = 1;
		ft_shoot(cube, image);
	}	
}

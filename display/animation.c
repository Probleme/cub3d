/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:03:29 by abizyane          #+#    #+#             */
/*   Updated: 2023/10/10 18:30:22 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/cub3d.h"

t_image	*lstnew_image(mlx_image_t *img)
{
	t_image	*new;

	new = ft_calloc(sizeof(t_image), 1);
	if (!new)
		return (NULL);
	if (line)
		new->shotgun = img;
	new->state = 0;
	new->nxt = NULL;
	return (new);
}

t_image	*last_image(t_image *head)
{
	t_image	*tmp;

	tmp = head;
	if (!head || !tmp->nxt)
		return (head);
	while (tmp->nxt->state > tmp->state)
		tmp = tmp->nxt;
	return (tmp);
}

void	lstadd_image(t_image **head, mlx_image_t *img)
{
	t_image	*new;
	t_image	*tmp;

	new = lstnew_image(img);
	tmp = *head;
	if (!tmp)
		(*head) = new;
	else
	{
		while (tmp && tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new;
	}
	  new->nxt = (*head);
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

void	init_animation(t_cube *cube)
{
		
		cube->mlx.img->gun.shotgun1 = mlx_load_png("textures/shotgun1.png");
		cube->mlx.img->gun.shotgun2 = mlx_load_png("textures/shotgun2.png");
		cube->mlx.img->gun.shotgun3 = mlx_load_png("textures/shotgun3.png");
		cube->mlx.img->gun.shotgun4 = mlx_load_png("textures/shotgun4.png");
		cube->mlx.img->gun.shotgun5 = mlx_load_png("textures/shotgun5.png");
		cube->mlx.img->gun.image = mlx_new_image(cube->mlx.mlx, 400, 300);
		mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->gun->shotgun1, WIDTH / 2, HEIGHT - 100);
		cube->mlx.img->gun->state = 0;
		mlx_delete_image(cube->mlx.mlx, cube->mlx.img->gun.shotgun1);

}


// void	ft_animate_sprites(t_cube *cube)
// {
// 	load_images(cube);
// 	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_BACKSPACE))
// 	{
		

// 	}

	

// }

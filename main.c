/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/12 16:47:40 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void ft_init_player(t_cube *cube)
{
	t_vect pos;
	char direction;

	pos.y = -1;
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
				cube->player.move_speed = 3;
				cube->player.rotation_speed = 4 * (M_PI / 180);	
				return ;
			}
		}
	}
	exit(ft_dprintf(2, "Failed to set initial player position\n"));
}

mlx_image_t *ft_draw_background(mlx_t *mlx, t_rgb *color)
{
	mlx_image_t *img;
	int col;
	int x;
	int y;

	img = mlx_new_image(mlx, WIDTH, HEIGHT / 2);
	if (!img)
		exit(ft_dprintf(2, "Failed to create background image\n"));
	col = ((unsigned int)color->red << 24) | ((unsigned int)color->green << 16) | ((unsigned int)color->blue << 8) | 255;
	x = 0;
	while (x < (int)img->height)
	{
		y = 0;
		while (y < (int)img->width)
		{
			mlx_put_pixel(img, y, x, col);
			y++;
		}
		x++;
	}
	return (img);
}

void ft_init_images(t_cube *cube)
{
	cube->mlx.img = malloc(sizeof(t_img));
	if (!cube->mlx.img)
		exit(ft_dprintf(2, "Failed to create image structure\n"));
	if (!(cube->mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false)))
		exit(ft_dprintf(2, "%s\n", mlx_strerror(mlx_errno)));
	cube->mlx.img->ceileing = ft_draw_background(cube->mlx.mlx, cube->parse->ceil_rgb);
	cube->mlx.img->floor = ft_draw_background(cube->mlx.mlx, cube->parse->floor_rgb);
	if (mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->ceileing, 0, 0) == -1)
		exit(ft_dprintf(2, "Failed to draw ceileing\n"));
	if (mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->floor, 0, HEIGHT / 2) == -1)
		exit(ft_dprintf(2, "Failed to draw floor"));
	cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
	if (!cube->mlx.img->walls)
		exit(ft_dprintf(2, "Failed to create walls image\n"));
	if (cube->parse->north)
	{
		cube->mlx.img->north = mlx_load_png(cube->parse->north);
		if (!cube->mlx.img->north)
			exit(ft_dprintf(2, "Failed to load north texture\n"));
	}
	if (cube->parse->south)
	{
		cube->mlx.img->south = mlx_load_png(cube->parse->south);
		if (!cube->mlx.img->south)
			exit(ft_dprintf(2, "Failed to load south texture\n"));
	}
	if (cube->parse->east)
	{
		cube->mlx.img->east = mlx_load_png(cube->parse->east);
		if (!cube->mlx.img->east)
			exit(ft_dprintf(2, "Failed to load east texture\n"));
	}
	if (cube->parse->west)
	{
		cube->mlx.img->west = mlx_load_png(cube->parse->west);
		if (!cube->mlx.img->west)
			exit(ft_dprintf(2, "Failed to load west texture\n"));
	}
	cube->mlx.img->door = mlx_load_png("./textures/door.png");
	if (!cube->mlx.img->door)
		exit(ft_dprintf(2, "Failed to load door texture\n"));
	cube->mlx.img->mini_map = mlx_new_image(cube->mlx.mlx, WIDTH * MINI_SCALE, HEIGHT * MINI_SCALE);
	if (!cube->mlx.img->mini_map)
		exit(ft_dprintf(2, "Failed to create mini map image\n"));
	if (mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->mini_map, 30, 20) == -1)
		exit(ft_dprintf(2, "Failed to draw mini map\n"));
	init_animation(cube);
	mlx_set_cursor_mode(cube->mlx.mlx, MLX_MOUSE_HIDDEN);
}

void ft_destroy_textures(t_cube *cube)
{
	if (cube->mlx.img->north)
		mlx_delete_texture(cube->mlx.img->north);
	if (cube->mlx.img->south)
		mlx_delete_texture(cube->mlx.img->south);
	if (cube->mlx.img->east) 
		mlx_delete_texture(cube->mlx.img->east);
	if (cube->mlx.img->west)
		mlx_delete_texture(cube->mlx.img->west);
	if (cube->mlx.img->door)
		mlx_delete_texture(cube->mlx.img->door);
}

int main(int argc, char **argv)
{
	t_cube cube;

	if (argc != 2)
		return (ft_dprintf(2, "Error\nInvalid number of arguments\n"));
	cube.parse = parsing(argv[1]);
	if (!cube.parse)
		exit (1);
	ft_init_player(&cube);
	cube.player.fov = (FOV_ANGLE * (M_PI / 180));
	cube.player.distance_proj_plane = (WIDTH / 2) / tan(cube.player.fov / 2);
	cube.rays = NULL;
	ft_init_images(&cube);
	init_doors(&cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_player_movement, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_minimap, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_cast_rays, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_draw_walls, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_animate_sprites, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_doors, &cube);
	mlx_loop(cube.mlx.mlx);
	if (cube.rays)
		free(cube.rays);
	ft_destroy_textures(&cube);
	mlx_terminate(cube.mlx.mlx);
	return (EXIT_SUCCESS);
}

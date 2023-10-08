/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/08 04:24:52 by ataouaf          ###   ########.fr       */
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
			if (cube->parse->map2d->map[(int)pos.y][(int)pos.x] == 'N' || cube->parse->map2d->map[(int)pos.y][(int)pos.x] == 'S' || cube->parse->map2d->map[(int)pos.y][(int)pos.x] == 'E' || cube->parse->map2d->map[(int)pos.y][(int)pos.x] == 'W')
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
					exit(printf("Failed to set initial player rotation"));
				cube->player.move_speed = 4;
				cube->player.rotation_speed = 4 * (M_PI / 180);	
				return ;
			}
		}
	}
	exit(printf("Failed to set initial player position"));
}

mlx_image_t *ft_draw_background(mlx_t *mlx, int color)
{
	mlx_image_t *img;
	int x;
	int y;

	img = mlx_new_image(mlx, WIDTH, HEIGHT / 2);
	if (!img)
		exit(printf("Failed to create background image"));
	x = 0;
	while (x < (int)img->height)
	{
		y = 0;
		while (y < (int)img->width)
		{
			mlx_put_pixel(img, y, x, color);
			y++;
		}
		x++;
	}
	return (img);
}

void ft_init_images(t_cube *cube)
{
	void *cursor;
	mlx_texture_t *texture;

	cube->mlx.img = malloc(sizeof(t_img));
	if (!(cube->mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false)))
		exit(printf("%s\n", mlx_strerror(mlx_errno)));
	cube->mlx.img->ceileing = ft_draw_background(cube->mlx.mlx, cube->parse->ceil);
	cube->mlx.img->floor = ft_draw_background(cube->mlx.mlx, cube->parse->floor);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->ceileing, 0, 0);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->floor, 0, HEIGHT / 2);
	cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
	if (!cube->mlx.img->walls)
		exit(printf("Failed to create walls image"));
	if (cube->parse->north)
		cube->mlx.img->north = mlx_load_png(cube->parse->north);
	if (cube->parse->south)
		cube->mlx.img->south = mlx_load_png(cube->parse->south);
	if (cube->parse->east)
		cube->mlx.img->east = mlx_load_png(cube->parse->east);
	if (cube->parse->west)
		cube->mlx.img->west = mlx_load_png(cube->parse->west);
	texture = mlx_load_png("textures/sniper_standing.png");
	cursor = mlx_create_cursor(texture);
	mlx_delete_texture(texture);
	mlx_set_cursor(cube->mlx.mlx, cursor);
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
}

int main(int argc, char **argv)
{
	t_cube cube;

	if (argc != 2)
		return (write(2, "Error\n", 6), 1);
	cube.parse = parsing(argv[1]);
	if (!cube.parse)
		exit (1);
	ft_init_player(&cube);
	cube.player.fov = (FOV_ANGLE * (M_PI / 180));
	cube.player.distance_proj_plane = (WIDTH / 2) / tan(cube.player.fov / 2);
	cube.rays = NULL;
	ft_init_images(&cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_player_movement, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_minimap, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_cast_rays, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_draw_walls, &cube);
	mlx_loop(cube.mlx.mlx);
	if (cube.rays)
		free(cube.rays);
	ft_destroy_textures(&cube);
	mlx_terminate(cube.mlx.mlx);
	return (EXIT_SUCCESS);
}

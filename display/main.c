/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/05 15:09:59 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_int_vect ft_getplayer_pos(char **map)
{
	t_int_vect pos;

	pos.y = 0;
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			if (map[pos.y][pos.x] == 'N' || map[pos.y][pos.x] == 'S' || map[pos.y][pos.x] == 'E' || map[pos.y][pos.x] == 'W')
				return (pos);
			pos.x++;
		}
		pos.y++;
	}
	return (pos);
}
//TODO: delete the textures after rendering

void ft_init_player(t_cube *cube)
{
	t_int_vect pos;

	pos = ft_getplayer_pos(cube->parse->map2d->map);
	cube->player.pos.x = pos.x * TILE_SIZE;
	cube->player.pos.y = pos.y * TILE_SIZE;
	if (cube->parse->map2d->map[pos.y][pos.x] == 'N')
		cube->player.angle = M_PI + M_PI_2;
	else if (cube->parse->map2d->map[pos.y][pos.x] == 'E')
		cube->player.angle = 0;
	else if (cube->parse->map2d->map[pos.y][pos.x] == 'S')
		cube->player.angle = M_PI_2;
	else if (cube->parse->map2d->map[pos.y][pos.x] == 'W')
		cube->player.angle = M_PI;
	cube->player.move_speed = 2;
	cube->player.rotation_speed = 4 * (M_PI / 180);	
	cube->player.walk_dir = 0;
	cube->player.turn_dir = 0;
	cube->player.fov = (FOV_ANGLE * (M_PI / 180));
	// cube->distance_proj_plane = (WIDTH / 2) / tan(cube->fov / 2);
	// cube->num_rays = (WIDTH / WALL_STRIP_WIDTH);
	// cube->rays = NULL;
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
	cube->mlx.img = malloc(sizeof(t_img));
	if (!(cube->mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
		exit(printf("%s\n", mlx_strerror(mlx_errno)));
	cube->mlx.img->ceileing = ft_draw_background(cube->mlx.mlx, cube->parse->ceil);
	cube->mlx.img->floor = ft_draw_background(cube->mlx.mlx, cube->parse->floor);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->ceileing, 0, 0);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->floor, 0, HEIGHT / 2);
	cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
	if (!cube->mlx.img->walls)
		exit(printf("Failed to create walls image"));
	cube->mlx.img->rays = NULL;
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
	{
		printf("Error\n");
		return (1);
	}
	cube.parse = parsing(argv[1]);
	if (!cube.parse)
		return (1);
	ft_init_player(&cube);
	ft_init_images(&cube);
	ft_load_png(&cube);
	// mlx_loop_hook(cube.mlx.mlx, &ft_cast_rays, &cube);
	// mlx_loop_hook(cube.mlx.mlx, &ft_draw_walls, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_player_movement, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_minimap, &cube);
	mlx_loop(cube.mlx.mlx);
	if (cube.rays)
		free(cube.rays);
	ft_destroy_textures(&cube);
	mlx_terminate(cube.mlx.mlx);
	return (EXIT_SUCCESS);
}

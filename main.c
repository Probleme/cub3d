/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/13 02:25:08 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void	ft_load_png(t_cube *cube)
{
	cube->mlx.img->north = mlx_load_png(cube->parse->north);
	if (!cube->mlx.img->north)
		exit(ft_dprintf(2, "Failed to load north texture\n"));
	cube->mlx.img->south = mlx_load_png(cube->parse->south);
	if (!cube->mlx.img->south)
		exit(ft_dprintf(2, "Failed to load south texture\n"));
	cube->mlx.img->east = mlx_load_png(cube->parse->east);
	if (!cube->mlx.img->east)
		exit(ft_dprintf(2, "Failed to load east texture\n"));
	cube->mlx.img->west = mlx_load_png(cube->parse->west);
	if (!cube->mlx.img->west)
		exit(ft_dprintf(2, "Failed to load west texture\n"));
	cube->mlx.img->door = mlx_load_png("./textures/door.png");
	if (!cube->mlx.img->door)
		exit(ft_dprintf(2, "Failed to load door texture\n"));
}

void	ft_init_images(t_cube *cube)
{
	cube->mlx.img = malloc(sizeof(t_img));
	if (!cube->mlx.img)
		exit(ft_dprintf(2, "Failed to create image structure\n"));
	cube->mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!cube->mlx.mlx)
		exit(ft_dprintf(2, "%s\n", mlx_strerror(mlx_errno)));
	cube->mlx.img->ceileing = ft_draw_background(cube->mlx.mlx,
			cube->parse->ceil_rgb);
	cube->mlx.img->floor = ft_draw_background(cube->mlx.mlx,
			cube->parse->floor_rgb);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->ceileing, 0, 0);
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->floor, 0, HEIGHT / 2);
	cube->mlx.img->walls = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT);
	if (!cube->mlx.img->walls)
		exit(ft_dprintf(2, "Failed to create walls image\n"));
	ft_load_png(cube);
	cube->mlx.img->mini_map = mlx_new_image(cube->mlx.mlx, WIDTH * MINI_SCALE,
			HEIGHT * MINI_SCALE);
	if (!cube->mlx.img->mini_map)
		exit(ft_dprintf(2, "Failed to create mini map image\n"));
	mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->mini_map, 30, 20);
	init_animation(cube, -1);
	mlx_set_cursor_mode(cube->mlx.mlx, MLX_MOUSE_HIDDEN);
}

void	ft_free_map2d(char **map2d)
{
	int	i;

	i = 0;
	while (map2d[i])
	{
		free(map2d[i]);
		i++;
	}
	free(map2d);
}

void	ft_destroy_textures(t_cube *cube)
{
	mlx_delete_texture(cube->mlx.img->north);
	mlx_delete_texture(cube->mlx.img->south);
	mlx_delete_texture(cube->mlx.img->east);
	mlx_delete_texture(cube->mlx.img->west);
	mlx_delete_texture(cube->mlx.img->door);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->ceileing);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->floor);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->walls);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->mini_map);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->target);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->screen);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->gun->shotgun[0]);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->gun->shotgun[1]);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->gun->shotgun[2]);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->gun->shotgun[3]);
	mlx_delete_image(cube->mlx.mlx, cube->mlx.img->gun->shotgun[4]);
	free(cube->mlx.img->gun);
	ft_free_map2d(cube->parse->map2d->map);
	free(cube->parse->map2d);
	free(cube->parse->ceil_rgb);
	free(cube->parse->floor_rgb);
	free(cube->parse);
	free(cube->mlx.img);
	free(cube->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	if (argc != 2)
		return (ft_dprintf(2, "Error\nInvalid number of arguments\n"));
	cube.parse = parsing(argv[1]);
	if (!cube.parse)
		exit(1);
	ft_init_player(&cube);
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

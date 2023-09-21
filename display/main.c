/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/21 07:27:05 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_image_t *decide_image(t_cube *cube, t_raycast ray)
{
	if (ray.wall_face == 'n')
		return (cube->mlx.img->north);
	if (ray.wall_face == 'e')
		return (cube->mlx.img->east);
	if (ray.wall_face == 's')
		return (cube->mlx.img->south);
	if (ray.wall_face == 'w')
		return (cube->mlx.img->west);
	return (NULL);
}

unsigned int ml_color_at(mlx_image_t *img, unsigned int x, unsigned int y)
{
	if (x >= img->width)
		x = img->width - 1;
	if (y >= img->height)
		y = img->height - 1;
	
	unsigned int *pixel = (unsigned int *)(img->pixels + (x + y * img->width) * sizeof(unsigned int));
	return *pixel;
}

void ft_draw_lines(t_img *img, mlx_image_t *texture, int i, float args[2], t_cube *cube)
{
	float texel_step = args[1];
	float height = args[0];
	unsigned int color;
	int j;

	if (height > HEIGHT)
		j = fmaxf((height - HEIGHT) / 2, 0);
	else
		j = 0;
	while (j < height && j + (HEIGHT - height) / 2 < HEIGHT)
	{
		color = ml_color_at(texture, texture->width * (cube->rays[i].pos_on_wall), j * texel_step);
		mlx_put_pixel(img->screen, i, j + (int)(HEIGHT - height) / 2, color);
		j++;
	}
}

void ft_draw_walls(void *param)
{
	t_cube *cube = (t_cube *)param;
	int i;
	float args[2];
	mlx_image_t *texture;
	
	i = -1;
	while (++i < WIDTH - 1)
	{
		texture = decide_image(cube, cube->rays[i]);
		if (!texture)
			continue;
		printf("cube->rays[i].eye_length = %f\n", cube->rays[i].eye_length);
		printf("cube->rays[i].pos_on_wall: %f\n", cube->rays[i].pos_on_wall);
		if (i == 10)
			exit(0);
		args[0] = fminf(fabsf(HEIGHT / cube->rays[i].eye_length), 10000000) + 2;
		args[1] = ((float)texture->height) / args[0];
		ft_draw_lines(cube->mlx.img, texture, i, args, cube);
	}
}

void ft_draw_colors(void* param)
{
	t_cube *cube = (t_cube *)param;
	unsigned int i;

	i = -1;
	while (++i < WIDTH * HEIGHT)
	{
		if (i < WIDTH * (HEIGHT / 2))
			mlx_put_pixel(cube->mlx.img->screen, i, 0, cube->parse->floor);
		else if (i > WIDTH * (HEIGHT / 2))
			mlx_put_pixel(cube->mlx.img->screen, i, 0, cube->parse->ceil);
	}
	if (mlx_is_key_down(cube->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx.mlx);
}

static void init_images(t_cube *cube)
{
	cube->mlx.img = malloc(sizeof(t_img));
	if (!(cube->mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
		exit(printf("%s\n", mlx_strerror(mlx_errno)));
	if (!(cube->mlx.img->screen = mlx_new_image(cube->mlx.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(cube->mlx.mlx);
		exit(printf("%s\n", mlx_strerror(mlx_errno)));
	}
	mlx_set_cursor_mode(cube->mlx.mlx, MLX_MOUSE_HIDDEN);
	if ((mlx_image_to_window(cube->mlx.mlx, cube->mlx.img->screen, 0, 0)) == -1)
	{
		mlx_close_window(cube->mlx.mlx);
		exit(printf("%s\n", mlx_strerror(mlx_errno)));
	}
	cube->ray_depth = 30;
	cube->fov = (80 * M_PI / 180);
	cube->pos_player = (t_float_vect){0, 0};
	cube->angle = 2.0 * M_PI;
}

int ft_is_in_wall(t_cube *cube, t_int_vect pos, char c)
{
	if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
	{
		if (cube->pos_player.x != 0)
			exit(printf("Error\nReassingning player position\n"));
		cube->pos_player = (t_float_vect){pos.x + .5, pos.y + .5};
		if (c == 'S')
			cube->angle += M_PI / 2;
		else if (c == 'N')
			cube->angle += M_PI + M_PI / 2;
		else if (c == 'W')
			cube->angle = M_PI;
		return (1);
	}
	return (c == '0');
}

void ft_do_check(t_cube *cube, t_int_vect pos)
{
	char c;

	c = map_get_at(cube->parse->map2d, pos.x, pos.y);
	if (ft_is_in_wall(cube, pos, c))
	{
		if (map_get_at(cube->parse->map2d, pos.x + 1, pos.y) == ' '
		|| map_get_at(cube->parse->map2d, pos.x - 1, pos.y) == ' '
		|| map_get_at(cube->parse->map2d, pos.x, pos.y + 1) == ' '
		|| map_get_at(cube->parse->map2d, pos.x, pos.y - 1) == ' '
		|| map_get_at(cube->parse->map2d, pos.x + 1, pos.y) == '\0'
		|| map_get_at(cube->parse->map2d, pos.x - 1, pos.y) == '\0'
		|| map_get_at(cube->parse->map2d, pos.x, pos.y + 1) == '\0'
		|| map_get_at(cube->parse->map2d, pos.x, pos.y - 1) == '\0')
			exit(printf("Error\nInvalid Map\n"));
	}
	else if (c != ' ' && c != '1')
		exit(printf("Error\nInvalid Map\n"));
}

void check_map(t_cube *cube)
{
	t_int_vect pos;

	pos.y = 0;
	while (pos.y < (int)cube->parse->map2d->length - 1)
	{
		pos.x = 0;
		if (cube->parse->map2d->map[pos.y][pos.x] == '\0')
			exit(printf("Error\nInvalid Map\n"));
		while (pos.x < (int)cube->parse->map2d->length -1)
		{
			ft_do_check(cube, pos);
			pos.x++;
		}
		pos.y++;
	}
	if (cube->pos_player.x == 0)
		exit(printf("Error\nInvalid Map\n"));
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
	init_images(&cube);
	ft_load_png(&cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_draw_colors, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_cast_rays, &cube);
	mlx_loop_hook(cube.mlx.mlx, &ft_draw_walls, &cube);
	mlx_loop(cube.mlx.mlx);
	mlx_terminate(cube.mlx.mlx);
	return (EXIT_SUCCESS);
}

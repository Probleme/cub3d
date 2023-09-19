/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/19 08:22:41 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void ft_hook(void* param)
// {
//     t_cube *cube = (t_cube *)param;
    
// }

void ft_main_hook(void* param)
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
    validate_map(&cube);
    mlx_loop_hook(cube.mlx.mlx, ft_main_hook, &cube);
    // mlx_loop_hook(cube.mlx.mlx, ft_hook, &cube);
    mlx_loop(cube.mlx.mlx);
    mlx_terminate(cube.mlx.mlx);
    return (EXIT_SUCCESS);
}

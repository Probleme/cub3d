/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/13 08:36:02 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
    fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
    const mlx_t* mlx = param;

    printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
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
    // MLX allows you to define its core behaviour before startup.
    mlx_set_setting(MLX_MAXIMIZED, true);
    cube.mlx.mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
    if (!cube.mlx.mlx)
        ft_error();

    /* Do stuff */

    // Create and display the image.
    cube.mlx.img.img = mlx_new_image(cube.mlx.mlx, 256, 256);
    if (!cube.mlx.img.img || (mlx_image_to_window(cube.mlx.mlx, cube.mlx.img.img, 0, 0) < 0))
        ft_error();

    // Even after the image is being displayed, we can still modify the buffer.
    mlx_put_pixel(cube.mlx.img.img, 0, 0, 0xFF0000FF);

    // Register a hook and pass mlx as an optional param.
    // NOTE: Do this before calling mlx_loop!
    mlx_loop_hook(cube.mlx.mlx, ft_hook, cube.mlx.mlx);
    mlx_loop(cube.mlx.mlx);
    mlx_terminate(cube.mlx.mlx);
    return (EXIT_SUCCESS);
}
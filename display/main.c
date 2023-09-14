/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:49:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/14 09:54:18 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_check_player_direction(t_cube *cube)
{
    if (cube->parse->player.direction == 'N')
        cube->pos.angle = -PI / 2;
    if (cube->parse->player.direction == 'S')
        cube->pos.angle = PI / 2;
    if (cube->parse->player.direction == 'E')
        cube->pos.angle = 0;
    if (cube->parse->player.direction == 'W')
        cube->pos.angle = PI;
}

void ft_init_cub_render(t_cube *cube)
{
    cube->pos.direction_x = cos(cube->pos.angle) * 5;
    cube->pos.direction_y = sin(cube->pos.angle) * 5;
    cube->data.focal = 0;
    cube->map_width = cube->parse->map1d->width;
    cube->map_height = cube->parse->map1d->height;
    cube->map_scale = 64;
    cube->pos.position_x = cube->map_scale * ((double)cube->parse->player.x + 0.5);
    cube->pos.position_y = cube->map_scale * ((double)cube->parse->player.y - 0.5);
    cube->mouse_grabbed = 0;
    cube->display_map = 0;
    cube->parse->player.y += 1;
}

int init_cub(t_cube *cube)
{
    cube->mlx.mlx = mlx_init(1920, 1080, "Cub3D", false);
    if (!cube->mlx.mlx)
        return (0);
    ft_check_player_direction(cube);
    ft_init_cub_render(cube);
    if (cube->map_height > cube->map_width)
        cube->map_max = cube->map_height;
    else
        cube->map_max = cube->map_width;
    
    return (1);   
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
    if (!init_cub(&cube))
    {
        printf("Error\nMLX failed to initialize\n");
        return (1);
    }
    mlx_loop(cube.mlx.mlx);
    return (EXIT_SUCCESS);
}

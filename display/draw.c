
#include "../inc/cub3d.h"

static int ft_calculate_texture_height_pixels(mlx_texture_t *texture, t_raycast ray, int draw_height)
{
    int height;
    double height_divided;

    if (ray.wall_height > HEIGHT)
        draw_height += (ray.wall_height - HEIGHT) / 2;
    height_divided = texture->height / ray.wall_height;
    height = floor((height_divided * draw_height)) * texture->width;
    return (height);
}

static double ft_calculate_texture_width_pixels(t_raycast ray, int texture_width)
{
    double width_pixels;

    if (ray.hit_horizontal)
        width_pixels = fmod(ray.horizontal_wall_hit.x, TILE_SIZE) / TILE_SIZE;
    else
        width_pixels = fmod(ray.vertical_wall_hit.y, TILE_SIZE) / TILE_SIZE;
    width_pixels *= texture_width;
    return (width_pixels);
}

int ft_get_colour_from_pixel(uint8_t *pixel)
{
    int color;

    color = pixel[0];
    color = (color << 8) + pixel[1];
    color = (color << 8) + pixel[2];
    return (color);
}

static int ft_get_texture_pixel_color(mlx_texture_t *texture, t_raycast ray, double current_height, int width_pixels)
{
    uint8_t *pixel;
    int pixel_texture_location;

    pixel_texture_location = ft_calculate_texture_height_pixels(texture, ray, current_height);
    pixel_texture_location += width_pixels;
    pixel_texture_location *= texture->bytes_per_pixel;
    pixel = &texture->pixels[pixel_texture_location];
    return (ft_get_colour_from_pixel(pixel));
}

void ft_draw_column(t_cube *cube, t_raycast ray, mlx_texture_t *texture, int x)
{
    int width;
    int current_height;
    int color;
    double width_pixels;

    x = x * WALL_STRIP_WIDTH;
    width_pixels = ft_calculate_texture_width_pixels(ray, texture->width);
    current_height = 0;
    while (ray.draw_start + current_height < ray.draw_end)
    {
        color = ft_get_texture_pixel_color(texture, ray, current_height, width_pixels);
        width = 0;
        while (width < WALL_STRIP_WIDTH)
        {
            mlx_put_pixel(cube->mlx.img->walls, x + width, ray.draw_start + current_height, color);
            width++;
        }
        current_height++;
    }
}

void ft_draw_info(t_raycast *rays, double distance_proj_plane, int num_rays)
{
    t_raycast *ray;
    int i;

    i = 0;
    while (i < num_rays)
    {
        ray = &rays[i];
        ray->wall_height = ((double)TILE_SIZE / ray->distance) * distance_proj_plane;
        ray->draw_start = (HEIGHT / 2) - (ray->wall_height / 2);
        ray->draw_end = ray->draw_start + ray->wall_height;
        if (ray->wall_height > HEIGHT)
        {
            ray->draw_start = 0;
            ray->draw_end = HEIGHT;
        }
        i++;
    }
}

// void ft_draw_walls(t_cube *cube, t_raycast *rays)
// {
//     int i;

//     rays = cube->rays;
//     i = 0;
//     ft_draw_info(rays, cube->distance_proj_plane, cube->num_rays);
//     while (i < cube->num_rays)
//     {
//         if (rays[i].wall_direction == NORTH)
//             ft_draw_column(cube, rays[i], cube->mlx.img->north, i);
//         else if (rays[i].wall_direction == SOUTH)
//             ft_draw_column(cube, rays[i], cube->mlx.img->south, i);
//         else if (rays[i].wall_direction == EAST)
//             ft_draw_column(cube, rays[i], cube->mlx.img->east, i);
//         else if (rays[i].wall_direction == WEST)
//             ft_draw_column(cube, rays[i], cube->mlx.img->west, i);
//         i++;
//     }
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 06:06:43 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/14 09:47:02 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>
#include "MLX42/MLX42.h"

# define PI 	3.1415926535

#define GNL_CLEAR 1
#define GNL_KEEP 0

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

typedef struct s_img
{
    void    *img;
    int     *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_img;

typedef struct s_mlx
{
    void    *mlx;
    // void    *win;
    t_img   img;
} t_mlx;
typedef struct s_data
{
    int     focal;
    int     shade;
    int     lineo;
    int     lineh;
    int     ratiox;
    int     ratioy;
    int     rayx;
    int     rayy;
    float   ra;
} t_data;
typedef struct s_pos
{
    float   position_x;
    float   position_y;
    float   direction_x;
    float   direction_y;
    float   angle;
    int     ipx;
    int     ipx_add_xo;
    int     ipx_sub_xo;
    int     ipy;
    int     ipy_add_yo;
    int     ipy_sub_yo;
    int     ipx_add_px;
    int     ipx_sub_px;
    int     ipy_add_py;
    int     ipy_sub_py;
    float   px;
    float   py;
    int     xo;
    int     yo;
} t_pos;

typedef struct s_map1d
{
    int width;
    int height;
    int *map;
} t_map1d;

typedef struct s_map2d
{
    int width;
    int height;
    char **map;
} t_map2d;

typedef struct s_player
{
    char direction;
    int x;
    int y;
} t_player;

typedef struct s_parse
{
    t_map1d *map1d;
    t_map2d *map2d;
    t_player player;
    char *north;
    char *south;
    char *east;
    char *west;
    int floor;
    int ceil;
} t_parse;

typedef struct s_cube
{
    t_mlx   mlx;
    t_parse *parse;
    t_pos   pos;
    t_data  data;
    int     map_width;
    int     map_height;
    int     map_max;
    int     map_scale;
    int     mouse_grabbed;
    int     display_map;
} t_cube;

char	*get_next_line(int fd, int clear);
char	*ft_strjoin1(char *s1, char *s2);

size_t ft_strlen(const char *str);
char *ft_strchr(char *s, int c);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int	ft_isdigit(int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char *ft_strappend(char **dest, char const *str);
int ft_atoi(const char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char **ft_split(char const *s, char c);
int ft_is_only(char *str, char c);

void ft_free_rgb(char **rgb, char *rgb_str);
char *ft_print_error(char *str);
void ft_free_parse(t_parse *parse);

t_parse *parsing(char *file);
char *ft_parse_map(t_parse *parse, char *line);
char *ft_extract_texture(t_parse *parse, char *line);
void *ft_extract_color(t_parse *parse, char *line);
int ft_fill_map(t_parse *parse, char **line, int fd);
char *ft_rgb_to_hexa_dec(char *rgb);
int ft_check_content(t_parse *parse);
int ft_check_char(char *line);
char **ft_parse_map2d(char *line);
int ft_check_player(t_parse *parse);
int ft_count_player(char **map, t_player *player);

#endif
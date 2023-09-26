/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 06:06:43 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/21 10:18:11 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080
# define TILE_SIZE 64
# define FOV_ANGLE 60
# define WALL_STRIP_WIDTH 1
# define MINI_SCALE 0.2

# define GNL_CLEAR 1
# define GNL_KEEP 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_float_vect
{
	float			x;
	float			y;
}					t_float_vect;

typedef struct s_int_vect
{
	int				x;
	int				y;
}					t_int_vect;

typedef struct s_img
{
	mlx_image_t		*screen;
		mlx_image_t		*north;
		mlx_image_t		*east;
		mlx_image_t		*west;
		mlx_image_t		*south;
	mlx_image_t		*ceileing;
	mlx_image_t		*floor;
	mlx_image_t		*walls;
	mlx_image_t		*rays;
	mlx_image_t		*mini_map;
}					t_img;

typedef struct s_mlx
{
	mlx_t			*mlx;
	t_img			*img;
}					t_mlx;

typedef struct s_map2d
{
	size_t			length;
	int				width;
	int				height;
	char			**map;
}					t_map2d;

typedef struct s_raycast
{
	double		ray_angle;
	t_float_vect	horizontal_step;
	t_float_vect	horizontal_wall_hit;
	t_float_vect	vertical_step;
	t_float_vect	vertical_wall_hit;
	float		distance;
	bool		hit_vertical;
	bool		hit_horizontal;
	bool		ray_facing_up;
	bool		ray_facing_right;
	// t_direction	hit_wall_direction;
	float		wall_height;
	int			draw_start;
	int			draw_end;
}					t_raycast;

typedef struct s_parse
{
	t_map2d			*map2d;
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	int				floor;
	int				ceil;
}					t_parse;

typedef struct s_player
{
	t_float_vect	pos;
	float			turn_dir;
	int				walk_dir;
	int				strafe_dir;
	float			rotation_angle;
	float			move_speed;
	float			rotation_speed;
}					t_player;

typedef struct s_cube
{
	t_mlx			mlx;
	t_parse			*parse;
	t_raycast		rays[WIDTH + 1];
	t_player		player;
	float			num_rays;
	float			distance_proj_plane;
	double			last_time;
	t_float_vect	pos_player;
	float			angle;
	float			fov;
}					t_cube;

char				*get_next_line(int fd, int clear);
char				*ft_strjoin_opt(char *s1, char *s2, int free_s1);

size_t				ft_strlen(const char *str);
char				*ft_strchr(char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s1);
int					ft_isdigit(int c);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strappend(char **dest, char *str);
int					ft_atoi(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_split(char const *s, char c);
int					ft_is_only(char *str, char c);

t_parse				*parsing(char *file);
char				*ft_parse_map(t_parse *parse, char *line);
char				*ft_extract_texture(t_parse *parse, char *line);
void				*ft_extract_color(t_parse *parse, char *line);
int					ft_fill_map(t_parse *parse, char **line, int fd);
char				*ft_rgb_to_hexa_dec(char *rgb);
int					ft_check_content(t_parse *parse);
int					ft_check_char(char *line);
char				**ft_parse_map2d(char *line, t_parse *parse);

void ft_load_png(t_cube *cube);
uint32_t			ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void ft_player_movement(void *param);

void				ft_cast_rays(void *param);
#endif
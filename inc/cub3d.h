/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 06:06:43 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/12 23:23:13 by ataouaf          ###   ########.fr       */
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

# define WIDTH 1440
# define HEIGHT 900
# define TILE_SIZE 64
# define FOV_ANGLE 60
# define WALL_STRIP_WIDTH 1
# define MINI_SCALE 0.2

# define GNL_CLEAR 1
# define GNL_KEEP 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct s_vect
{
	double			x;
	double			y;
}					t_vect;

typedef struct s_door
{
	int				index;
	int				x;
	int				y;
	int				state;
	struct s_door	*nxt;
}					t_door;

typedef struct s_image
{
	mlx_image_t		*shotgun[5];
	int				state;
	int				i;
	int				j;
	int				curr;
}					t_image;

typedef struct s_img
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
	mlx_texture_t	*door;
	mlx_image_t		*screen;
	mlx_image_t		*ceileing;
	mlx_image_t		*floor;
	mlx_image_t		*walls;
	mlx_image_t		*mini_map;
	t_image			*gun;
	mlx_image_t		*target;
}					t_img;

typedef struct s_mlx
{
	mlx_t			*mlx;
	t_img			*img;
}					t_mlx;

typedef struct s_map2d
{
	int				width;
	int				height;
	char			content;
	char			**map;
}					t_map2d;

typedef enum e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	DOOR
}					t_direction;

typedef struct s_raycast
{
	double			ray_angle;
	t_vect			horizontal_step;
	t_vect			horizontal_wall_hit;
	t_vect			vertical_step;
	t_vect			vertical_wall_hit;
	double			distance;
	int				hit_vertical;
	int				hit_horizontal;
	int				ray_facing_up;
	int				ray_facing_right;
	t_direction		wall_direction;
	double			wall_height;
	int				draw_start;
	int				draw_end;
}					t_raycast;

typedef struct s_parse
{
	t_map2d			*map2d;
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	t_door			*doors;
	t_rgb			*floor_rgb;
	t_rgb			*ceil_rgb;
}					t_parse;

typedef struct s_player
{
	t_vect			pos;
	double			rotation_angle;
	double			move_speed;
	double			rotation_speed;
	float			distance_proj_plane;
	double			fov;
}					t_player;

typedef struct s_cube
{
	t_mlx			mlx;
	t_parse			*parse;
	t_raycast		*rays;
	t_player		player;
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
int					is_player(char c);
int					ft_dprintf(int fd, const char *str, ...);

t_parse				*parsing(char *file);
char				*ft_parse_map(t_parse *parse, char *line);
void				*ft_extract_texture(t_parse *parse, char *line);
char				*ft_rgb_to_hexa_dec(char *rgb);
int					ft_check_content(t_parse *parse);
int					ft_check_char(char *line);
char				**ft_parse_map2d(char *line, t_parse *parse);
void				ft_cast_rays(void *param);
void				ft_draw_walls(void *param);
int					ft_check_map(char **map);
char				*ft_get_str(char *line);
t_rgb				*ft_get_rgb(char *line);

void				ft_player_movement(void *param);
void				ft_minimap(void *param);
void				init_doors(t_cube *cube);
void				ft_doors(void *param);
void				init_animation(t_cube *cube, int i);
void				ft_animate_sprites(void *param);

void				ft_find_horizontal_wall(t_cube *cube, t_raycast *ray);
void				ft_find_vertical_wall(t_cube *cube, t_raycast *ray);
int					ft_check_is_wall(t_map2d *map, double x, double y);

#endif
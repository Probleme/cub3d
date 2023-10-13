/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:10:37 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/12 22:14:49 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_get_str(char *line)
{
	int	i;
	int	len;
	int	size;

	len = 2;
	while (line[len] == ' ')
		len++;
	i = len;
	size = 0;
	while (line[i + size] != '\n')
	{
		size++;
		if (ft_is_only(line + i + size, ' ') && line[i + size + 1] != '\n')
			break ;
	}
	return (ft_substr(line, i, size));
}

void	*ft_extract_texture(t_parse *parse, char *line)
{
	char	**texture;

	texture = NULL;
	if (!ft_strncmp("NO", line, 2))
		texture = &(parse->north);
	if (!ft_strncmp("SO", line, 2))
		texture = &(parse->south);
	if (!ft_strncmp("WE", line, 2))
		texture = &(parse->west);
	if (!ft_strncmp("EA", line, 2))
		texture = &(parse->east);
	if (texture)
	{
		if (*texture != NULL)
			exit(ft_dprintf(2,
					"Error\nYou can't set a texture more than once\n"));
		*texture = ft_get_str(line);
		if (!*texture)
			return (0);
	}
	return (*texture);
}

static char	**ft_split_color(char *rgb_str)
{
	char	**rgb;
	int		i;
	int		j;

	i = -1;
	j = -1;
	rgb = ft_split(rgb_str, ',');
	if (!rgb)
		return ((void *)0);
	while (rgb[++i])
	{
		while (rgb[i][++j])
			if (!(rgb[i][j] >= '0' && rgb[i][j] <= '9'))
				exit(ft_dprintf(2,
						"Error\nRGB string format must be number\n"));
		j = -1;
	}
	if (i != 3)
		exit(ft_dprintf(2, "Error\nRGB string format is not valid\n"));
	return (rgb);
}

static void	ft_free_split(char **rgb)
{
	int	i;

	i = -1;
	while (rgb[++i])
	{
		free(rgb[i]);
		rgb[i] = NULL;
	}
	free(rgb);
	rgb = NULL;
}

t_rgb	*ft_get_rgb(char *line)
{
	char	**rgb;
	char	*rgb_str;
	int		i;
	int		j;
	t_rgb	*color;

	i = -1;
	j = -1;
	rgb_str = ft_get_str(line);
	if (!rgb_str)
		exit(ft_dprintf(2, "Error\ncan't get RGB string\n"));
	rgb = ft_split_color(rgb_str);
	color = malloc(sizeof(t_rgb));
	if (!color)
		return ((void *)0);
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	if ((color->red < 0 || color->red > 255) && (color->green < 0
			|| color->green > 255) && (color->blue < 0 || color->blue > 255))
		exit(ft_dprintf(2, "Error\nRGB must be in 0 - 255 range\n"));
	free(rgb_str);
	ft_free_split(rgb);
	return (color);
}

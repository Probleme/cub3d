/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:10:37 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/13 20:13:24 by abizyane         ###   ########.fr       */
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

static int	array_len(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

static char	**ft_split_color(char *rgb_str)
{
	char	**rgb;
	char	**rgb_splited;
	int		i;
	int		j;

	i = -1;
	j = -1;
	rgb = ft_split(rgb_str, ',');
	if (!rgb)
		return ((void *)0);
	while (rgb[++i])
	{
		rgb_splited = ft_split(rgb[i], ' ');
		while (!rgb_splited[0] || rgb_splited[0][++j])
			if (!rgb_splited[0] || !(rgb_splited[0][j] >= '0' && \
				rgb_splited[0][j] <= '9') || array_len(rgb_splited) != 1)
				exit(ft_dprintf(2,
						"Error\nRGB string format is invalid\n"));
		ft_free_split(rgb_splited);
		j = -1;
	}
	if (i != 3 || check_commas(rgb_str))
		exit(ft_dprintf(2, "Error\nRGB string format is not valid\n"));
	return (rgb);
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
	if (color->red < 0 || color->red > 255 || color->green < 0
		|| color->green > 255 || color->blue < 0 || color->blue > 255)
		exit(ft_dprintf(2, "Error\nRGB must be in 0 - 255 range\n"));
	free(rgb_str);
	ft_free_split(rgb);
	return (color);
}

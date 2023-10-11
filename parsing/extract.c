/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:10:37 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/11 06:15:01 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lens;
	char	*str;

	if (!s)
		return (0);
	i = 0;
	lens = ft_strlen(s);
	if (lens <= start)
		return (ft_strdup(""));
	if (len >= ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s[start] && len--)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

int	ft_is_only(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

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

void *ft_extract_texture(t_parse *parse, char *line)
{
	char **texture;

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


t_rgb  *ft_get_rgb(char *line)
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
		return ((void *)0);
	rgb = ft_split(rgb_str, ',');
	if (!rgb)
		return ((void *)0);
	while (rgb[++i])
		while (rgb[i][++j])
			if (!(rgb[i][j] >= '0' && rgb[i][j] <= '9'))
				exit(ft_dprintf(2, "Error\nRGB string format is not valid\n"));
	if (i != 3)
		exit(ft_dprintf(2, "Error\nRGB string format is not valid\n"));
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
	free(rgb);
	return (color);
}

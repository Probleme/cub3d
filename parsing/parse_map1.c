/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 07:23:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/13 20:52:12 by abizyane         ###   ########.fr       */
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
	str = ft_calloc(len + 1, sizeof(char));
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

static int	ft_get_infos(t_parse *parse, char **line, int fd)
{
	while (*line != NULL)
	{
		if ((!ft_strncmp("F ", *line, 2) && parse->floor_rgb)
			|| (!ft_strncmp("C ", *line, 2) && parse->ceil_rgb))
			exit(ft_dprintf(2,
					"Error\nYou can't set a color more than once\n"));
		if (!ft_strncmp("F ", *line, 2))
			parse->floor_rgb = ft_get_rgb(*line);
		else if (!ft_strncmp("C ", *line, 2))
			parse->ceil_rgb = ft_get_rgb(*line);
		else if (!ft_strncmp("NO ", *line, 3) || !ft_strncmp("SO ", *line, 3)
			|| !ft_strncmp("WE ", *line, 3) || !ft_strncmp("EA ", *line, 3))
			ft_extract_texture(parse, *line);
		else if (!(ft_strlen(*line) == 1 && (*line)[0] == '\n'))
			return (1);
		free(*line);
		*line = get_next_line(fd, GNL_KEEP);
	}
	return (1);
}

static char	*ft_get_map_content(t_parse *parse, char **line, int fd)
{
	char	*map;

	map = ft_strdup("");
	while (*line != NULL)
	{
		if (!ft_check_content(parse))
			exit(ft_dprintf(2, "Error\n Invalid Map\n"));
		else if (!ft_check_char(*line))
			exit(ft_dprintf(2, "Error\nMap contains invalid characters\n"));
		else if (ft_strlen(*line) == 1 && *line[0] == '\n')
			exit(ft_dprintf(2, "Error\nMap contains empty lines\n"));
		else if (ft_is_only(*line, ' '))
			exit(ft_dprintf(2, "Error\nMap contains only spaces\n"));
		else
		{
			map = ft_strappend(&map, *line);
			if (!map)
				exit(ft_dprintf(2, "Error\nMalloc failed\n"));
		}
		free(*line);
		*line = get_next_line(fd, GNL_KEEP);
	}
	return (map);
}

char	*ft_parse_map(t_parse *parse, char *file)
{
	int		fd;
	char	*line;
	char	*map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(ft_dprintf(2, "Error\nFile not found\n"));
	line = get_next_line(fd, GNL_KEEP);
	if (!ft_get_infos(parse, &line, fd))
		exit(EXIT_FAILURE);
	map = ft_get_map_content(parse, &line, fd);
	if (!map)
		exit(EXIT_FAILURE);
	if (ft_strlen(map) == 0)
		exit(ft_dprintf(2, "Error\nMap is empty\n"));
	return (map);
}

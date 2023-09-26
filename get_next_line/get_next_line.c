/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 03:04:46 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/19 05:37:16 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (save[++i] && save[i] != '\n')
		line[i] = save[i];
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!new_save)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

char	*ft_read_and_save(int fd, char *save)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(save, '\n') && bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		save = ft_strjoin_opt(save, buffer, 1);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd, int clear)
{
	char		*line;
	static char	*save[10480];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 10480)
		return (NULL);
	save[fd] = ft_read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	save[fd] = ft_save(save[fd]);
	if (clear == 1)
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (line);
}

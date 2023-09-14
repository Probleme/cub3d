/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 07:23:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/14 04:55:01 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int check_is_empty(char *line)
{
    if (ft_strlen(line) == 1 && line[0] == '\n')
        return (1);
    return (0);
}

static int ft_check_extension(char *file)
{
    int i;

    i = 0;
    while (file[i])
        i++;
    if ( i < 4)
        return (0);
    if (file[i - 1] == 'b' && file[i - 2] == 'u' && file[i - 3] == 'c' && file[i - 4] == '.')
        return (1);
    return (0);
}

int ft_fill_map(t_parse *parse, char **line, int fd)
{
    while (*line != NULL)
    {
        if (!ft_strncmp("F", *line, 1) || !ft_strncmp("C", *line, 1))
        {
            if (!ft_extract_color(parse, *line))
                return (ft_free_parse(parse), free(*line), free(get_next_line(fd, GNL_CLEAR)), 0);
        }
        else if (!ft_strncmp("NO", *line, 2) || !ft_strncmp("SO", *line, 2) || !ft_strncmp("WE", *line, 2) || !ft_strncmp("EA", *line, 2))
        {
            if (!ft_extract_texture(parse, *line))
                return (ft_free_parse(parse), free(*line), free(get_next_line(fd, GNL_CLEAR)), 0);
        }
        else if (!check_is_empty(*line))
            return (1);
        free(*line);
        *line = get_next_line(fd, GNL_KEEP);
    }
    return (1);
}

static int ft_check_is_valid(char *line)
{
    if (!ft_check_char(line))
    {
        printf("Error\nMap contains invalid characters\n");
        return (0);
    }
    else if (check_is_empty(line))
    {
        printf("Error\nMap is empty (empty lines)\n");
        return (0);
    }
    else if (ft_is_only(line, ' '))
    {
        printf("Error\nMap contains only spaces on line\n");
        return (0);
    }
    return (1);
}

static char *ft_get_content(t_parse *parse, char **line, int fd)
{
    char *map;

    map = ft_strdup("");
    while (*line != NULL)
    {
        if (!ft_check_content(parse))
        {
            printf("Error\nMissing content textures or colors\n");
            exit(1);
        }
        else if (!ft_check_is_valid(*line))
            exit(1);
        else
        {
            map = ft_strappend(&map, *line);
            if (!map)
                return (ft_free_parse(parse), free(*line), free(get_next_line(fd, GNL_CLEAR)), NULL);
        }
        free(*line);
        *line = get_next_line(fd, GNL_KEEP);
    }
    return (map);
}

char *ft_parse_map(t_parse *parse, char *file)
{
    int fd;
    char *line;
    char *map;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (ft_free_parse(parse), ft_print_error("Error\nCan't open file\n"), NULL);
    if (!ft_check_extension(file))
        return (ft_free_parse(parse), ft_print_error("Error\nWrong extension\n"), NULL);
    line = get_next_line(fd, GNL_KEEP);
    if (!ft_fill_map(parse, &line, fd))
        return (NULL);
    map = ft_get_content(parse, &line, fd);
    if (!map)
        return (NULL);
    if (ft_strlen(map) == 0) // free map
        return (ft_free_parse(parse), ft_print_error("Error\nEmpty map\n"), NULL);
    return (map);
}

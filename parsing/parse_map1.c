/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 07:23:47 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/09 06:44:50 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int ft_is_empty(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

static int ft_check_extension(char *file)
{
    int i;

    i = 0;
    while (file[i])
        i++;
    if (file[i - 1] == 'b' && file[i - 2] == 'u' && file[i - 3] == 'c' && file[i - 4] == '.')
        return (1);
    return (0);
}

static int ft_fill_map(t_parse *parse, char **line, int fd)
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
        else if (!ft_is_empty(*line))
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
        printf("Error\nMap conatins invalid characters\n");
        return (0);
    }
    else if (ft_strlen(line) == 1 && line[0] == '\n')
    {
        printf("Error\nMap is empty\n");
        return (0);
    }
    else if (!ft_check_map(line))
    {
        printf("Error\nMap is not valid\n");
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
            printf("Error\nMissing conten textures or colorst\n");
            exit(1);
        }
        else if (!ft_check_is_valid(*line))
        {
            printf("Error\nMap is not valid\n");
            exit(1);
        }
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
        return (ft_free_parse(parse), ft_print_error("Error\nCan't open file\n"));
    if (!ft_check_extension(file))
        return (ft_free_parse(parse), ft_print_error("Error\nWrong extension\n"));
    line = get_next_line(fd, GNL_KEEP);
    if (!ft_fill_map(parse, &line, fd))
        return (NULL);
    map = ft_get_content(parse, &line, fd);
    if (!map)
        return (NULL);
    
    return (line);
}
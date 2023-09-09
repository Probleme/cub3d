/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:10:37 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/09 05:22:01 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int ft_is_only(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != c && str[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

char *ft_get_str(char *line)
{
    size_t cur;
    int len;

    len = 2; // to skip the prefix (NO, SO, WE, EA)
    while (line[len] == ' ')
        len++;
    cur = len;
    size_t size = 0;
    while (line[cur + size] != '\n')
    {
        size++;
        if (ft_is_only(line + cur + size, ' ') && line[cur + size + 1] != '\n')
            break;
    }
    return ft_substr(line, cur, size);
}

char *ft_extract_texture(t_parse *parse, char *line)
{
    int fd;
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
            return (ft_print_error("Error\n(You can't set a texture more than once)\n"));
        *texture = ft_get_str(line);
        if (!*texture)
            return (0);
        fd = open(*texture, O_RDONLY);
        if (fd < 0)
            return (ft_print_error("Error\n(Unable to open texture file)\n"));
    }
    return (*texture);
}

int *ft_get_color_num(t_parse *parse, char *line)
{
    if (!ft_strncmp("C", line, 1))
        return &(parse->ceil);
    else if (!ft_strncmp("F", line, 1))
        return &(parse->floor);
    else
        return NULL;
}

void *ft_extract_color(t_parse *parse, char *line)
{
    int *color_num;
    char *color;
    int i;
    char *pos;
    char *hex;

    color_num = ft_get_color_num(parse, line);
    if (*color_num != -1)
        return ft_print_error("Error\n(You can't set a color more than once)\n");
    color = ft_rgb_to_hexa_dec(ft_get_str(line));
    if (!color)
        return NULL;
    i = 0;
    *color_num = 0;
    hex = "0123456789ABCDEF";
    while (color[i])
    {
        pos = ft_strchr(hex, color[i++]);
        *color_num = *color_num * 16 + pos - hex;
    }
    free(color);
    return ((void *)1);
}

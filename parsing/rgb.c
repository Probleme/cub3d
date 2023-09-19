/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:57:49 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/19 02:17:33 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int ft_check_string_format(char *rgb)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (rgb[i])
    {
        if (rgb[i] == ',')
        {
            count++;
            if (count > 2)
                return (0);
        }
        else if (rgb[i] == '+')
        {
            if (!ft_isdigit(rgb[i + 1]))
                return (0);
        }
        else if (!ft_isdigit(rgb[i]))
            return (0);
        i++;
    }
    return (1);
}

static char **ft_rgb_to_array(char *rgb)
{
    char **rgb_split;

    if (!ft_check_string_format(rgb))
        exit (printf("Error\nRGB string format is not valid\n"));
    rgb_split = ft_split(rgb, ',');
    if (!rgb_split)
        exit (printf("Error\nMalloc failed\n"));
    return (rgb_split);
}

static char *ft_dec_to_hex(int decimal)
{
    char *hex;
    int i;

    if (decimal < 0 || decimal > 255)
        return (NULL);
    hex = ft_calloc(3, sizeof(char));
    if (!hex)
        return (NULL);
    ft_memset(hex, '0', 2);
    i = 1;
    while (decimal > 0)
    {
        hex[i--] = "0123456789ABCDEF"[decimal % 16];
        decimal /= 16;
    }
    return (hex);
}

char *ft_rgb_to_hexa_dec(char *rgb)
{
    char **rgb_split;
    char *hex;
    char *color;
    int i;

    color = ft_strdup("");
    rgb_split = ft_rgb_to_array(rgb);
    if (!rgb_split)
        return (free(color), NULL);
    i = 0;
    while (rgb_split[i])
    {
        if (ft_atoi(rgb_split[i]) < 0 || ft_atoi(rgb_split[i]) > 255)
            exit (printf("Error\nColor must between [0, 255]\n"));
        hex = ft_dec_to_hex(ft_atoi(rgb_split[i++]));
        if (!hex)
            exit (EXIT_FAILURE);
        color = ft_strappend(&color, hex);
        if (!color)
            exit (EXIT_FAILURE);
        free(hex);
    }
    ft_free_rgb(rgb_split, rgb);
    return (color);
}

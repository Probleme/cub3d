/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 06:36:06 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/10 20:42:05 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	else
		return (0);
}

static int	check_directions(char **map, int i, int j)
{
	if (!map[i + 1] || (map[i + 1][j] != '1' && map[i + 1][j] != '0'\
		&& !is_player(map[i + 1][j]) && map[i + 1][j] != '2'))
			return (1);
	else if (!map[i - 1] || (map[i - 1][j] != '1' && map[i - 1][j] != '0'\
		&& !is_player(map[i - 1][j]) && map[i - 1][j] != '2'))
			return (1);
	else if (!map[i][j + 1] || (map[i][j + 1] != '1' && map[i][j + 1] != '0'\
		&& !is_player(map[i][j + 1]) && map[i][j + 1] != '2'))
			return (1);
	else if (!map[i][j - 1] || (map[i][j - 1] != '1' && map[i][j - 1] != '0'\
		&& !is_player(map[i][j - 1]) && map[i][j - 1] != '2'))
			return (1);
	else
		return (0);
}

int ft_check_map(char **map)
{
    int		i;
    int		j;
	
    i = 0;
	while (map[i])
    {
		j = 0;
		while (map[i][j])
		{
			// printf("%d, %d\n", i, j);
			if ((map[i][j] == '0' || map[i][j] == '2') && check_directions(map, i, j))
				return (write(2, "Map Error!!\n", 12));
			j++;
		}
		i++;
	}
	return (0);
}

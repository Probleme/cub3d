/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 06:36:06 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/18 22:25:34 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	column_size(char **map, int idx)
{
	int	i;

	i = 0;
	while (map[i][idx] == ' ')
		i++;
	while (map[i][idx] != 0 && map[i][idx] != ' ')
		i++;
	return (i);
}

static int	row_size(char **map, int idx)
{
	int	i;

	i = 0;
	while (map[idx][i] == ' ')
		i++;
	while (map[idx][i] != 0 && map[idx][i] != ' ')
		i++;
	return (i);
}


// void	flood_fill(char ***map, int x, int y); if there is any other cases this should solve the problem

int	ft_check_map(t_parse *parse) // checks the borders of the map
{
	// t_map2d *map2d;
	// t_player player;
	// int count;
	char	**map;
	int i;
	int j;
	
	i = 0;
	j = 0;
	map = parse->map2d->map;
	while(map[i])
	{
		if (map[i][0] != 1 || map[i][row_size(map[i]) - 1] != 1)
			return (0);
		i++;
	}
	while (map[i][j])
	{
		if (map[0][j] != 1 || map[column_size(map, j) - 1][j])
			return (0);
		j++;
	}
	return (1);
} 
	// map[x][0] == 1
	// map[x][max] == 1
	// map[0][y] == 1
	// map[max][y] == 1
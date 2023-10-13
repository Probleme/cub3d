/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 06:36:06 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/13 17:45:48 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	count_player(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W' || map[i][j] == 'S')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	else
		return (0);
}

int	check_door(char **map, int i, int j)
{
	if (map[i + 1][j] && map[i - 1][j] && map[i + 1][j] == '1'
			&& map[i - 1][j] == '1')
		return (0);
	if (map[i][j + 1] && map[i][j - 1] && map[i][j + 1] == '1'
			&& map[i][j - 1] == '1')
		return (0);
	else
		return (1);
}

static int	check_directions(char **map, int i, int j, t_vect max)
{
	if (j - 1 < 0 || i - 1 < 0 || i + 1 > max.y || j + 1 > max.x)
		return (1);
	if (map[i + 1][j] != '1' && map[i + 1][j] != '0'
			&& !is_player(map[i + 1][j]) && map[i + 1][j] != '2')
		return (1);
	else if (map[i - 1][j] != '1' && map[i - 1][j] != '0'
			&& !is_player(map[i - 1][j]) && map[i - 1][j] != '2')
		return (1);
	else if (map[i][j + 1] != '1' && map[i][j + 1] != '0'
			&& !is_player(map[i][j + 1]) && map[i][j + 1] != '2')
		return (1);
	else if (map[i][j - 1] != '1' && map[i][j - 1] != '0'
			&& !is_player(map[i][j - 1]) && map[i][j - 1] != '2')
		return (1);
	else
		return (0);
}

int	ft_check_map(char **map, t_vect max)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || map[i][j] == '2') && check_directions(map,
					i, j, max))
				exit(ft_dprintf(2, "Error\nThe Map is invalid\n"));
			if (is_player(map[i][j]) && check_directions(map, i, j, max))
				exit(ft_dprintf(2, "Error\nThe player position is invalid\n"));
			if (is_player(map[i][j]) && count_player(map) != 1)
				exit(ft_dprintf(2, "Error\nOnly one Player is available\n"));
			if (map[i][j] == '2' && check_door(map, i, j))
				exit(ft_dprintf(2, "Error\nThe door must be between walls\n"));
			j++;
		}
		i++;
	}
	return (0);
}

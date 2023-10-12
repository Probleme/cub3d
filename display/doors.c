/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:52:48 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/12 23:21:04 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_door	*lstnew_door(int x, int y, int index)
{
	t_door	*new;

	new = ft_calloc(sizeof(t_door), 1);
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->index = index;
	new->state = 0;
	new->nxt = NULL;
	return (new);
}

static void	lstadd_door(t_door **head, int x, int y, int index)
{
	t_door	*new;
	t_door	*tmp;

	new = lstnew_door(x, y, index);
	tmp = *head;
	if (!tmp)
		(*head) = new;
	else
	{
		while (tmp && tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new;
	}
}

void	init_doors(t_cube *cube)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (cube->parse->map2d->map[i])
	{
		j = 0;
		while (cube->parse->map2d->map[i][j])
		{
			if (cube->parse->map2d->map[i][j] == '2')
				lstadd_door(&cube->parse->doors, j, i, count++);
			j++;
		}
		i++;
	}
}

static int	in_door_range(t_cube *cube, t_door *curr_door)
{
	int	x;
	int	y;

	x = (int)cube->player.pos.x / TILE_SIZE;
	y = (int)cube->player.pos.y / TILE_SIZE;
	if (curr_door->y == y && (curr_door->x == (x + 1) || curr_door->x == (x
				- 1)))
		return (1);
	else if (curr_door->x == x && (curr_door->y == (y + 1) || curr_door->y == (y
				- 1)))
		return (1);
	else if (x == curr_door->x && y == curr_door->y)
		return (1);
	return (0);
}

void	ft_doors(void *param)
{
	t_door	*door;
	char	**map;
	t_cube	*cube;

	cube = param;
	door = cube->parse->doors;
	map = cube->parse->map2d->map;
	while (door)
	{
		if (!door->state && in_door_range(cube, door))
		{
			door->state = 1;
			map[door->y][door->x] = '0';
		}
		else if (door->state && !in_door_range(cube, door))
		{
			door->state = 0;
			map[door->y][door->x] = '2';
		}
		door = door->nxt;
	}
}

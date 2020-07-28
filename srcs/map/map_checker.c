/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:35:07 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/27 14:28:11 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include <stdio.h>

static int	check_horizontal(t_map map)
{
	__uint32_t	x;
	__uint32_t	y;
	int			last;
	int			current;

	x = 0;
	while (x < map.size_x + 1)
	{
		y = 0;
		last = -1;
		while (y < map.size_y + 1)
		{
			current = last;
			if (x >= map.size_x || y >= map.size_y)
				last = -1;
			else
				last = map.map[y][x]->id;
			if (current + last == CUB_VOID)
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

static int	check_vertical(t_map map)
{
	__uint32_t	x;
	__uint32_t	y;
	int			last;
	int			current;

	y = 0;
	while (y < map.size_y + 1)
	{
		x = 0;
		last = -1;
		while (x < map.size_x + 1)
		{
			current = last;
			if (x >= map.size_x || y >= map.size_y)
				last = -1;
			else
				last = map.map[y][x]->id;
			if (current + last == CUB_VOID)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int			check_map(t_map map)
{
	int	status;

	status = 0;
	status += check_horizontal(map);
	status += check_vertical(map);
	return (status == 0);
}

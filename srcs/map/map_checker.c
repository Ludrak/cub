/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:23:20 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/06 13:33:52 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include <stdio.h>

//TODO ALGORITHM : 2D ARRAY READING USING 2 WHILE
int                         check_map(t_map map)
{
    __uint32_t  x;
    __uint32_t  y;
    int         last;
    int         current;

    last = -1;
    x = 0;
    while (x < map.size_x)
    {
        y = 0;
        while (y < map.size_y)
        {
            current = last;
            last = map.map[y][x]->id;
            if (current + last == CUB_VOID)
            {
                printf ("x: %d, y: %d\n", x, y);
                return (0);
            }
            y++;
        }
        x++;
    }
    last = -1;
    y = 0;
    while (y < map.size_y)
    {
        x = 0;
        while (x < map.size_x)
        {
            current = last;
            last = map.map[y][x]->id;
            if (current + last == CUB_VOID)
            {
                printf ("x: %d, y: %d\n", x, y);
                return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

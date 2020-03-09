/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:09 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/09 22:22:38 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "map_utils.h"

t_map       *create_map(unsigned int size_x, unsigned int size_y)
{
    t_map   *map;
    unsigned int     i;
    
    if (!(map = malloc(sizeof(t_map))))
        return (NULL);
    map->size_x = size_x;
    map->size_y = size_y;
    if (!(map->map = ft_calloc(size_y + 1, sizeof(__uint8_t *))))
        return (NULL);
    i = 0;
    while (i < size_y)
        if (!(map->map[i++] = ft_calloc(size_x + 1, sizeof(__uint8_t))))
            return (NULL);
    return (map);
}
#include <stdio.h>
void        print_map(t_map map)
{
    __uint32_t  i;
    __uint32_t  j;

    j = 0;
    while (j < map.size_x)
    {
        i = 0;
        while (i < map.size_y)
            printf ("%d ", map.map[i++][j]);
        j++;
        printf ("\n");
    }
}
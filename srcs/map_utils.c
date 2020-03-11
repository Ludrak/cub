/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:09 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/11 19:50:20 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"


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


void        print_map(t_map map)
{
    __uint32_t  i;
    __uint32_t  j;

    j = 0;
    while (j < map.size_x)
    {
        i = 0;
        while (i < map.size_y)
        {
            if (map.map[i][j] == CUB_VOID)
                write (1, "  ", 2);
            if (map.map[i][j] == CUB_AIR)
                write (1, "\u253C\u253C", 6);
            if (map.map[i][j] == CUB_BLOCK)
                write (1, "\u2588\u2588", 6);
           i++;
        }
        j++;
        write (1, "\n", 1);
    }
}


void        draw_minimap(t_image *buffer, t_map map, t_vec2d pos)
{
    __uint32_t  i;
    __uint32_t  j;
    t_vec2d c_pos;
    int     color;
    
    j = 0;
    draw_rect_to_buffer(buffer, 
                        pos, 
                        create_vector(map.size_y * (MINIMAP_CUB_SIZ + 2),
                        map.size_x * (MINIMAP_CUB_SIZ + 2)),
                        0xFFFFFF);
    while (j < map.size_x)
    {
        i = 0;
        while (i < map.size_y)
        {
            if (map.map[i][j] == CUB_AIR)
                color = 0xe3e3e8;
            else if (map.map[i][j] == CUB_BLOCK)
                color = 0x4c4c4c;
            else
                color = 0x202023;
            c_pos.x = pos.x + i * (MINIMAP_CUB_SIZ + 2);
            c_pos.y = pos.y + j * (MINIMAP_CUB_SIZ + 2);
            draw_rect_to_buffer(buffer, c_pos, create_vector(MINIMAP_CUB_SIZ, MINIMAP_CUB_SIZ), color);
            i++;
        }
        j++;
    }
}
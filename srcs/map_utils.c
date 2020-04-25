/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:09 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/25 14:03:18 by lrobino          ###   ########.fr       */
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
    if (!(map->map = ft_calloc(size_y + 1, sizeof(t_cube **)))) // __uint_8t*
        return (NULL);
    i = 0;
    while (i < size_y)
        if (!(map->map[i++] = ft_calloc(size_x + 1, sizeof(t_cube *)))) // __uint8_t
            return (NULL);
    return (map);
}


void        print_map(t_map map)
{
    __uint32_t  i;
    __uint32_t  j;

    write (1, "[MAP - CUB3D]\n", 14);
    j = 0;
    while (j < map.size_x)
    {
        i = 0;
        while (i < map.size_y)
        {
            // TODO
            // FIX OLD CUBE STRUCT
            
            if (map.map[i][j]->id == CUB_VOID)
                write (1, "  ", 2);
            if (map.map[i][j]->id == CUB_AIR)
                write (1, "\u254B\u254B", 6);
            else
                write (1, "\u2588\u2588", 6);
           i++;
        }
        j++;
        write (1, "\n", 1);
    }
}


void        draw_minimap(t_image *buffer, t_engine engine, t_vec2f pos)
{
    __uint32_t      i;
    __uint32_t      j;
    t_vec2f         c_pos;
    t_color         color;

    j = 0;
    draw_rect_to_buffer(buffer, 
                        create_vectorf(pos.x - 2, pos.y - 2), 
                        create_vectorf(engine.map.size_y * (MINIMAP_CUB_SIZ + 1) + 4,
                        engine.map.size_x * (MINIMAP_CUB_SIZ + 1) + 4),
                        create_gray(31));
    while (j < engine.map.size_x)
    {
        i = 0;
        while (i < engine.map.size_y)
        {
            if (engine.map.map[i][j]->id == CUB_AIR)
                color.value = 0xe3e3e8;
            else if (engine.map.map[i][j]->id != CUB_VOID)
                color.value = 0x4c4c4c;
            else
                color.value = 0x202023;
            
            
            c_pos.x = pos.x + i * (MINIMAP_CUB_SIZ + 1);
            c_pos.y = pos.y + j * (MINIMAP_CUB_SIZ + 1);
            draw_rect_to_buffer(buffer, c_pos, create_vectorf(MINIMAP_CUB_SIZ, MINIMAP_CUB_SIZ), color);

            if (i == (__uint32_t)floor(engine.player.pos.x) && j == (__uint32_t)floor(engine.player.pos.y))
            {
                draw_rect_to_buffer(buffer, create_vectorf((int)(engine.player.pos.x * (float)MINIMAP_CUB_SIZ) - 5 + i,
                                                        (int)(engine.player.pos.y * (float)MINIMAP_CUB_SIZ) - 5 + j),
                                            create_vectorf(10, 10), create_color(255, 0, 0));
            }
            i++;
        }
        j++;
    }
}
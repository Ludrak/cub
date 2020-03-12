/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:32 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 11:47:10 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

#include "engine.h"

# define MINIMAP_CUB_SIZ    10

# define CUB_VOID   0
# define CUB_AIR    1
# define CUB_BLOCK  2

typedef struct  s_map
{
    __uint8_t   **map;
    __uint32_t  size_x;
    __uint32_t  size_y;
}               t_map;

t_map       *create_map(unsigned int size_x, unsigned int size_y);
void        destroy_map(t_map *map);

//UTIL
void        print_map(t_map map);
void        draw_minimap(t_image *buffer, t_map map, t_vec2d pos);


#endif
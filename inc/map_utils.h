/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:32 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 20:57:24 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

#include "engine.h"

# define MINIMAP_CUB_SIZ    20

# define CUB_VOID           -1
# define CUB_AIR            0
# define CUB_BLOCK          1
# define CUB_BLOCK_TORCH    2
# define CUB_BLOCK_CRACKED  3

t_map       *create_map(unsigned int size_x, unsigned int size_y);
void        destroy_map(t_map *map);


//UTIL
void        print_map(t_map map);
void        draw_minimap(t_image *buffer, t_engine engine, t_vec2f pos);
int		    is_on_map(t_map map, float x, float y);


#endif
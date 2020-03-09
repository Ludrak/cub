/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:32 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/09 19:36:45 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

#include <stdlib.h>
#include "libft.h"

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

#endif
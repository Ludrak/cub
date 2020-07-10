/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:32 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/10 16:37:52 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

# include "vectors.h"
# include "cube.h"

# define MINIMAP_CUB_SIZ    20

# define CUB_VOID           -1
# define CUB_AIR            0
# define CUB_BLOCK          1
# define CUB_BLOCK_TORCH    2
# define CUB_BLOCK_CRACKED  3

typedef struct	s_map
{
	t_cube		***map;
	__uint32_t	size_x;
	__uint32_t	size_y;
}				t_map;

void			destroy_map(t_map *map);
int				is_on_map(t_map map, float x, float y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:44:10 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 17:05:57 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <math.h>
# include "libft.h"
# include "vectors.h"
# include "mlx.h"

# define __PROJECT_NAME "Cub3d - 1.0"

# define MAX_VIEW       10000



typedef struct  s_window
{
    void        *ptr;
    int         size_x;
    int         size_y;
}               t_window;

typedef struct	s_image
{
	void		*img_ptr;
	int			*data;

	int			size_l;
	int			bpp;
	int			endian;
    t_vec2d     size;
}               t_image;

typedef struct  s_player
{
    t_vec2d     pos;
    t_vec2d     dir;
    float       rot;
    float       fov;
}               t_player;

typedef struct  s_map
{
    __uint8_t   **map;
    __uint32_t  size_x;
    __uint32_t  size_y;
}               t_map;

typedef struct  s_engine
{
    void        *ptr;
    t_window    win;
    t_image     buf;
    t_map       map;
    t_player    player;
}               t_engine;

# include "map_utils.h"
# include "raycast.h"
# include "graphics.h"
# include "map_parser.h"

/*
**  MATH UTILS
*/
float   radians (float deg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:44:10 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/20 19:02:43 by lrobino          ###   ########.fr       */
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

# define MAX_VIEW       24
# define VIEW_HEIGHT    1000


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
    t_vec2f     size;
}               t_image;

typedef struct  s_player
{
    t_vec2d     pos;
    t_vec2d     dir;
    float       rot;
    float       fov;
    float       speed;
    t_vec2f     vel;
}               t_player;

typedef struct  s_map
{
    __uint8_t   **map;
    __uint32_t  size_x;
    __uint32_t  size_y;
}               t_map;

typedef struct	s_key
{
	char		value;
	char		pressed;
}				t_key;

typedef struct	s_control_keys
{
	t_key		up;
	t_key		down;
	t_key		left;
	t_key		right;
    t_key       escape;
}				t_control_keys;

typedef struct  s_engine
{
    void            *ptr;
    t_window        win;
    t_image         buf;
    t_map           map;
    t_player        player;
    t_control_keys  keys;
}               t_engine;

# include "map_utils.h"
# include "raycast.h"
# include "graphics.h"
# include "map_parser.h"

/*
**  MATH UTILS
*/
float   radians (float deg);
float   max(float a, float b);
int     constrain(int value, int min, int max);


/*
**  INPUTS
*/
t_control_keys  set_key_values();
int             key_released_event(int key, void *engine_ptr);
int             key_pressed_event(int key, void *engine_ptr);

#endif

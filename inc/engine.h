/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:44:10 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/25 13:19:55 by lrobino          ###   ########.fr       */
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

# define __PROJECT_NAME "Cub3d - 1.1.0"

# define MAX_VIEW       10
# define VIEW_HEIGHT    720
# define VIEW_WIDTH     720


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
    t_vec2i     size;
}               t_image;

typedef struct  s_player
{
    t_vec2d     pos;
    t_vec2d     dir;
    float       rot;
    float       rotZ;
    float       fov;
    float       speed;
    t_vec2f     vel;
}               t_player;

typedef struct  s_cube
{
    t_image     tex;
    short       id;
}               t_cube;


typedef struct  s_map
{
    //__uint8_t   **map;
    t_cube      ***map;
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

    t_list          *cubes;

    //TEXTURES
    t_image         cub_tex_left;
    t_image         cub_tex_right;
    t_image         cub_tex_top;
    t_image         cub_tex_bottom;
    t_image         cub_tex_floor;
    t_image         cub_tex_ceil;
}               t_engine;

# include "map_utils.h"
# include "raycast.h"
# include "graphics.h"
# include "process.h"
# include "map_parser.h"

/*
**  CUBE UTILS
*/
int         register_cube(t_engine *eng, char *tex_file, short id);
t_cube      *get_cube_by_id(t_engine *eng, short id);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:01:28 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 16:11:10 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <math.h>
# include <X11/X.h>
# include "libft.h"
# include "vectors.h"
# include "mlx.h"

# define __PROJECT_NAME "Cub3d - 1.2.0"

# define MAX_VIEW       10

//THOSE ARE THE HEIGHT OF THE SCREEN TODO REPLACE
# define VIEW_HEIGHT    720
# define VIEW_WIDTH     720

# define CREATED_WIN    1
# define CREATED_CAM    2
# define CREATED_PLAYER 4
# define CREATED_MAP    8
# define CREATED_CUBES  16
# define CREATED_SPRITE 32

# define PLAYER_SPEED   10.0F // 12.0F if custom
# define ROTATION_SPEED 0.08F; // 0.12F if custom


typedef struct  s_window
{
    void        *ptr;
    int         size_x;
    int         size_y;
}               t_window;

typedef struct  s_camera
{
    float       fov;
    float       height;
    float       l_angle;
    float       r_angle;
    float       *z_buffer;
}               t_camera;

typedef struct	s_image
{
	void		*img_ptr;
	int			*data;

	int			sl;
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
    t_vec2d     plane;
}               t_player;

typedef struct  s_cube
{
    short       id;
    t_image     *tex[5];
}               t_cube;

typedef __uint8_t t_face;
typedef struct  s_cast
{
    float   wall_h;
    float   offset;
    float   scale_f;

    float   dist;
    t_vec2d point;
    t_face  face;
    float   face_pos;
    t_cube  *cube;
    t_image *tex;
}               t_cast;


typedef struct  s_map
{
    t_cube      ***map;
    __uint32_t  size_x;
    __uint32_t  size_y;
}               t_map;

typedef struct	s_key
{
	int 		value;
	char		pressed;
}				t_key;

typedef struct	s_control_keys
{
	t_key		up;
	t_key		down;
	t_key		left;
	t_key		right;
    t_key       escape;
    t_key       show_map;
    t_key       take_screenshot;
}				t_control_keys;


typedef struct  s_color_channel
{
    int     b : 8;
    int     g : 8;
    int     r : 8;
}               t_color_channel;

typedef union   u_color
{
    t_color_channel channel;
    unsigned int value : 24;
}               t_color;

typedef struct  s_engine
{
    //MLX
    void            *ptr;
    t_window        win;
    t_image         buf;
    t_camera        cam;

    int             allocs;
    int             format;
    
    t_player        player;
    
    //INPUT
    t_control_keys  keys;
    
    //MAP
    t_map           map;
    t_list          *cubes;
    t_list          *loaded_sprites;
    t_list          *sprites;

    t_color         floor_col;
    t_color         ceil_col;
    t_image         *tex_floor;
    t_image         *tex_ceil;
    t_image         *textures[4]; // TEXTURES OF WALLS, ONLY USED WHEN FORMAT
    t_list          *loaded_textures;
    t_list          *animations;
}               t_engine;


# include "map_utils.h"
# include "raycast.h"
# include "graphics.h"
# include "process.h"
# include "sprite.h"
# include "map_parser.h"
# include "parser.h"


/*
**  REGISTER HANDLER
*/
void	register_builtins(t_engine *eng);
int		register_cube_format(t_engine *eng, short id);

/*
**  UNLOADING HANDLER
*/
void	print_exit_status(int status);
void    unload_cubes(t_engine *eng);
void    unload_sprites(t_engine *eng);
void    unload_textures(t_engine *eng);
void    unload_map(t_engine *eng);



/*
**  PLAYER UTILS
*/
t_player	create_player(t_engine *eng, t_vec2d pos, float rot, float speed);
void		move_player(t_player *player, int dir, t_map map);
void		rotate_player(t_player *player, int dir);



/*
**  CAMERA UTILS
*/
void	init_camera(t_engine *eng, t_camera *cam, float fov);
void	destroy_camera(t_camera *cam);


/*
**  CUBE UTILS
*/
int         register_cube(t_engine *eng, char *tex_file, short id);
void	    unload_cube(t_list *cube);
t_cube      *get_cube_by_id(t_engine *eng, short id);

/*
**  MATH UTILS
*/
float   rad(float deg);
float   deg(float rad);
float   max(float a, float b);
int     constrain(int value, int min, int max);


/*
**  WINDOW & HOOKS
*/
int             create_window(t_engine *eng, int sizeX, int sizeY, char *title);
void            set_hooks(t_engine *eng);
int             on_window_destroyed(void *eng);

/*
**  INPUT UTILS
*/
void            handle_input(t_engine *eng);
t_control_keys  set_key_values();
int             key_released_event(int key, void *engine_ptr);
int             key_pressed_event(int key, void *engine_ptr);

/*
**  BMP UTILS
*/
int			export_frame(t_engine *eng, char *name);
void        take_screenshot(t_engine *eng);


#endif

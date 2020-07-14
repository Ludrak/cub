/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:00:14 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/11 14:29:14 by lrobino          ###   ########.fr       */
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
# include "graphics.h"
# include "map_utils.h"
# include "raycast.h"
# include "sprite.h"
# include "map_parser.h"
# include "parser.h"
# include "ft_printf.h"

# define __PROJECT_NAME	"Cub3d - 1.2.0"

# define MAX_VIEW		10

/*
**  THOSE ARE DEPRECATED
**  DO NOT USE FOR FURTHER
**  IMPLEMENTATION
*/
# define VIEW_HEIGHT	720
# define VIEW_WIDTH		720

# define CREATED_WIN	1
# define CREATED_CAM	2
# define CREATED_PLAYER	4
# define CREATED_MAP	8
# define CREATED_CUBES	16
# define CREATED_SPRITE	32

# define PLAYER_SPEED	10.0F
# define ROTATION_SPEED	0.08F

# define __FRICTION		1.3F

typedef struct	s_window
{
	void		*ptr;
	int			size_x;
	int			size_y;
}				t_window;

typedef struct	s_camera
{
	float		fov;
	float		height;
	float		l_angle;
	float		r_angle;
	float		*z_buffer;
}				t_camera;

typedef struct	s_player
{
	t_vec2d		pos;
	t_vec2d		dir;
	float		rot;
	float		fov;
	float		speed;
	t_vec2f		vel;
	t_vec2d		plane;
}				t_player;

typedef struct	s_key
{
	int			value;
	char		pressed;
}				t_key;

typedef struct	s_control_keys
{
	t_key		up;
	t_key		down;
	t_key		left;
	t_key		right;
	t_key		escape;
	t_key		show_map;
	t_key		take_screenshot;
	t_key		l_cam;
	t_key		r_cam;
}				t_control_keys;

typedef struct	s_engine
{
	void			*ptr;
	t_window		win;
	t_image			buf;
	t_camera		cam;
	int				allocs;
	int				format;
	t_player		player;
	t_control_keys	keys;
	t_map			map;
	t_list			*cubes;
	t_list			*loaded_sprites;
	t_list			*sprites;
	t_color			floor_col;
	t_color			ceil_col;
	t_image			*tex_floor;
	t_image			*tex_ceil;
	t_image			*textures[4];
	t_list			*loaded_textures;
	t_list			*animations;
	char			*map_file;
	int				first_screen;
}				t_engine;

/*
**	PARSER UTILS
*/
void			parse_registry(t_engine *eng, char *file);
int				parse_map(t_engine *eng, t_list *lines);

/*
**  REGISTER HANDLER
*/
void			register_builtins(t_engine *eng);
int				register_cube_format(t_engine *eng, short id);

/*
**  UNLOADING HANDLER
*/

void			print_exit_status(int status);
void			unload_cubes(t_engine *eng);
void			unload_sprites(t_engine *eng);
void			unload_textures(t_engine *eng);
void			unload_map(t_engine *eng);

/*
**  PLAYER UTILS
*/

t_player		create_player
		(t_engine *eng, t_vec2d pos, float rot, float speed);
void			update_player(t_player *player, t_map map);
void			move_player(t_player *player, int dir, float ldir);
void			rotate_player(t_player *player, int dir);

/*
**  CAMERA UTILS
*/

void			init_camera(t_engine *eng, t_camera *cam, float fov);
void			destroy_camera(t_camera *cam);

/*
**  CUBE UTILS
*/

int				register_cube(t_engine *eng, char *tex_file, short id);
void			unload_cube(t_list *cube);
t_cube			*get_cube_by_id(t_engine *eng, short id);

/*
**  MATH UTILS
*/

float			rad(float deg);
float			deg(float rad);
float			max(float a, float b);
int				constrain(int value, int min, int max);

/*
**	RAYCAST UTILS
*/
t_cast			perform_raycast
		(t_engine *eng, t_vec2d pos, t_vec2d r_dir, t_map map);
void			cast_to_frame_buffer(t_image *buffer, t_engine *engine);

/*
**  WINDOW & HOOKS
*/

int				create_window
		(t_engine *eng, int size_x, int size_y, char *title);
void			set_hooks(t_engine *eng);
int				on_window_destroyed(void *eng);

/*
**  INPUT UTILS
*/

void			handle_input(t_engine *eng);
t_control_keys	set_key_values();
int				key_released_event(int key, void *engine_ptr);
int				key_pressed_event(int key, void *engine_ptr);

/*
**	MAP UTILS
*/
t_map			create_map
	(unsigned int size_x, unsigned int size_y, t_engine *eng);
void			draw_minimap(t_image *buffer, t_engine engine, t_vec2f pos);

/*
**	SPRITE UTILS
*/
void			render_sprite(t_engine eng, t_image *buf);
t_spt_info		create_spt_info(t_engine eng, t_sprite tmp);
int				register_sprite(t_engine *eng, char *texture, int sprite_id);
int				add_sprite
		(t_engine *eng, int sprite_id, t_vec2d pos, float size);
t_sprite		*get_sprite_by_id(t_engine *eng, int id);

/*
**	IMAGE UTILS
*/

int				load_images(t_engine *engine);
int				load_from_xpm(char *xpm, t_image **img, t_engine *engine);
void			draw_ray_to_buffer(t_engine *eng, int x, t_cast cast);

/*
**  BMP UTILS
*/

int				export_frame(t_engine *eng, char *name);
void			take_screenshot(t_engine *eng);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/25 14:02:41 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"
#include <stdio.h>

void    awake(t_engine *eng)
{
	eng->ptr = mlx_init();
	if (!loadImages(eng))
		p_exit(eng, "Error while loading images.", STATUS_IMG_FAILED);
	eng->cubes = NULL;

	
	register_cube(eng, NULL, CUB_VOID);	//VOID
	register_cube(eng, NULL, CUB_AIR);	//AIR
	register_cube(eng, "res/textures/dungeon_wall.png", CUB_BLOCK);
	register_cube(eng, "res/textures/dungeon_wall_torch.png", CUB_BLOCK_TORCH);
	register_cube(eng, "res/textures/dungeon_wall_cracked.png", CUB_BLOCK_CRACKED);
}

void    setup(t_engine *engine)
{
	t_map		*map;
	t_player	player;
	int			map_fd;

	//WINDOW SETUP
	engine->win.size_x	= 1280;	//TODO PARSE
	engine->win.size_y	= 720;	//TODO PARSE
	if (!(engine->win.ptr = mlx_new_window(engine->ptr, engine->win.size_x, engine->win.size_y, __PROJECT_NAME)))
		return ;

	//SETUP FRAME IMAGE BUFFER INFO
	engine->buf.size = create_vectori(engine->win.size_x, engine->win.size_y);
	
	//PLAYER SETUP
	engine->player.pos = create_vector(0, 0);
	engine->player.fov = 90.0f;
	engine->player.rot = 0;
	engine->player.rotZ = 0;
	engine->player.speed = 6;
	
	//MAP SETUP
	if ((map_fd = open("res/maps/map.cub", O_RDONLY)) > 0)
	{
		map = parse_map(map_fd, engine);
		engine->map = *map;
		printf("[MAP] Checking map bounds...\n");
		if (!check_map(engine->map) || (!player.pos.x && !player.pos.y))
		{
			printf("[MAP] Error : INVALID MAP FORMAT\n");
			p_exit(engine, "Invalid map format.", STATUS_MAP_FAILED);
		}
		else
			printf("[MAP] Valid map format.\n");
		close (map_fd);
	}

	//HOOKS
	mlx_loop_hook(engine->ptr, runtime, engine);
	engine->keys = set_key_values();
	mlx_hook(engine->win.ptr, 3, 0, key_pressed_event, engine);
    mlx_hook(engine->win.ptr, 2, 0, key_released_event, engine);

	mlx_loop(engine->ptr);
}

int    runtime (t_engine *engine)
{	
	//SETUP FRAME IMAGE BUFFER
	engine->buf.img_ptr = mlx_new_image(engine->ptr, engine->buf.size.x, engine->buf.size.y);
	engine->buf.data = (int *)mlx_get_data_addr(engine->buf.img_ptr, &engine->buf.bpp, &engine->buf.size_l,
		&engine->buf.endian);

	if (engine->keys.left.pressed)
        engine->player.rot += 0.06f;
    if (engine->keys.right.pressed)
        engine->player.rot -= 0.06f;

	if (engine->keys.up.pressed)
    {
		engine->player.vel.x = -cos(engine->player.rot) * engine->player.speed * 0.01f;
		engine->player.vel.y = -sin(engine->player.rot) * engine->player.speed * 0.01f;

		if (engine->map.map[(int)floorf(engine->player.pos.x + engine->player.vel.x * 10.0f)][((int)floorf(engine->player.pos.y))]->id == CUB_AIR)//CUB_BLOCK)
			engine->player.pos.x += engine->player.vel.x;
		if (engine->map.map[(int)floorf(engine->player.pos.x)][((int)floorf(engine->player.pos.y + engine->player.vel.y * 10.0f))]->id == CUB_AIR)//CUB_BLOCK)
			engine->player.pos.y += engine->player.vel.y;

		//engine->player.rotZ+=0.1f;
    }
    if (engine->keys.down.pressed)
	{
		engine->player.vel.x = cos(engine->player.rot) * engine->player.speed * 0.01f;;
		engine->player.vel.y = sin(engine->player.rot) * engine->player.speed * 0.01f;
		
		if (engine->map.map[(int)floorf(engine->player.pos.x + engine->player.vel.x * 10.0f)][((int)floorf(engine->player.pos.y))]->id == CUB_AIR)//CUB_BLOCK)
			engine->player.pos.x += engine->player.vel.x;
		if (engine->map.map[(int)floorf(engine->player.pos.x)][((int)floorf(engine->player.pos.y + engine->player.vel.y * 10.0f))]->id == CUB_AIR)//CUB_BLOCK)
			engine->player.pos.y += engine->player.vel.y;
		//engine->player.rotZ -= 0.1f;
    }

	if (engine->keys.escape.pressed)
		p_exit(engine, "Escape key pressed", STATUS_SUCCESS);
	
	cast_to_frame_buffer(&engine->buf, engine);
	draw_minimap(&engine->buf, *engine, create_vectorf(0, 0));

	mlx_put_image_to_window(engine->ptr, engine->win.ptr, engine->buf.img_ptr, 0, 0);
	mlx_destroy_image(engine->ptr, engine->buf.img_ptr);
	return (0);
}

void    p_exit (t_engine *engine, char *info_log, int status)
{
	printf ("[EXIT]<REQUEST> : %s\n[EXIT] Clearing data...\n", info_log);
	if (status != STATUS_IMG_FAILED)
		mlx_destroy_window(engine->ptr, engine->win.ptr);
	free(engine);
	printf ("[EXIT] Done.");
	exit(0);
}

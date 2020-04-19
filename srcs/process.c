/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/19 11:01:33 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"
#include <stdio.h>

void    awake(t_engine *eng)
{
	eng->ptr = mlx_init();
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
	engine->buf.size = create_vector(engine->win.size_x, engine->win.size_y);
	
	//MAP SETUP
	if ((map_fd = open("map.cub", O_RDONLY)) > 0)
	{
		map = parse_map(map_fd);
		engine->map = *map;
		printf("Checking map bounds...\n");
		if (!check_map(engine->map))
		{
			printf("Error : INVALID MAP FORMAT\n");
			//p_exit(engine);
		}
		else
			printf("Valid map format.\n");
		close (map_fd);
	}

	//PLAYER SETUP
	player.pos = create_vector(2.5f, 2.5f);
	player.dir = create_vector(1.0f, 0.0f);
	player.fov = 50.0f;
	player.rot = 0;
	player.speed = 4;
	engine->player = player;

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

	engine->player.vel = create_vector(0, 0);
	if (engine->keys.up.pressed)
    {
		engine->player.vel.x = -cos(engine->player.rot) * engine->player.speed * 0.01f;
		engine->player.vel.y = -sin(engine->player.rot) * engine->player.speed * 0.01f;
    }
    if (engine->keys.down.pressed)
	{
		engine->player.vel.x = cos(engine->player.rot) * engine->player.speed * 0.01f;;
		engine->player.vel.y = sin(engine->player.rot) * engine->player.speed * 0.01f;
    }

	if (engine->map.map[(int)floorf(engine->player.pos.x + engine->player.vel.x)][((int)floorf(engine->player.pos.y))] != CUB_BLOCK)
		engine->player.pos.x += engine->player.vel.x;
	if (engine->map.map[(int)floorf(engine->player.pos.x)][((int)floorf(engine->player.pos.y + engine->player.vel.y))] != CUB_BLOCK)
		engine->player.pos.y += engine->player.vel.y;
	printf ("POS : x:%f, y:%f\n", engine->player.pos.x, engine->player.pos.y);

	cast_to_frame_buffer(&engine->buf, *engine);
	draw_minimap(&engine->buf, *engine, create_vector(0, 0));

	mlx_put_image_to_window(engine->ptr, engine->win.ptr, engine->buf.img_ptr, 0, 0);
	return (0);
}

void    p_exit (t_engine *engine)
{
	mlx_destroy_window(engine->ptr, engine->win.ptr);
	free(engine);
	exit(0);
}

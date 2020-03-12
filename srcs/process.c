/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 19:30:52 by lrobino          ###   ########lyon.fr   */
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
			p_exit(engine);
		}
		else
			printf("Valid map format.\n");
		close (map_fd);
	}

	//PLAYER SETUP
	player.pos = create_vector(3.1, 3.1);
	player.dir = create_vector(1.2, 0.4);
	player.fov = 80.0f;
	player.rot = 0;
	engine->player = player;
	//t_cast cast;
	//cast = perform_raycast(engine->player, engine->player.dir, engine->map);
	//printf ("dir : %f cast =>> x : %f, y : %f\n", engine->player.dir.y, cast.point.x, cast.point.y);
	//p_exit(engine);

	//HOOKS
	mlx_loop_hook(engine->ptr, runtime, engine);
	
	mlx_loop(engine->ptr);
}

int    runtime (t_engine *engine)
{
	static float x, y;
	
	//SETUP FRAME IMAGE BUFFER
	engine->buf.img_ptr = mlx_new_image(engine->ptr, engine->buf.size.x, engine->buf.size.y);
	engine->buf.data = (int *)mlx_get_data_addr(engine->buf.img_ptr, &engine->buf.bpp, &engine->buf.size_l,
		&engine->buf.endian);

	engine->player.rot += 0.01;

	// engine->player.dir.x = sin(x);
	// engine->player.dir.y = sin(y);
	//if (engine->player.pos.y < engine->map.size_x - 2)
	//	engine->player.pos.y += 0.1;

	//cast_to_frame_buffer(&engine->buf, *engine);


	draw_minimap(&engine->buf, *engine, create_vector(40, 40));
	//draw_rect_to_buffer(&engine->buf, create_vector(121, 10), create_vector(200, 400), create_color(100, 20, 20));
	x+= 0.1;
	y+= .1;
	mlx_put_image_to_window(engine->ptr, engine->win.ptr, engine->buf.img_ptr, 0, 0);
	return (0);
}

void    p_exit (t_engine *engine)
{
	mlx_destroy_window(engine->ptr, engine->win.ptr);
	free(engine);
	exit(0);
}

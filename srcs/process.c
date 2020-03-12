/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 11:55:31 by lrobino          ###   ########lyon.fr   */
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

	//HOOKS
	mlx_loop_hook(engine->ptr, runtime, engine);
	
	mlx_loop(engine->ptr);
}

int    runtime (t_engine *engine)
{
	//SETUP FRAME IMAGE BUFFER
	engine->buf.img_ptr = mlx_new_image(engine->ptr, engine->buf.size.x, engine->buf.size.y);
	engine->buf.data = (int *)mlx_get_data_addr(engine->buf.img_ptr, &engine->buf.bpp, &engine->buf.size_l,
		&engine->buf.endian);

	draw_minimap(&engine->buf, engine->map, create_vector(40, 40));

	//draw_rect_to_buffer(&engine->buf, create_vector(121, 10), create_vector(200, 400), create_color(100, 20, 20));
	
	mlx_put_image_to_window(engine->ptr, engine->win.ptr, engine->buf.img_ptr, 0, 0);
	return (0);
}

void    p_exit (t_engine *engine)
{
	mlx_destroy_window(engine->ptr, engine->win.ptr);
	free(engine);
	exit(0);
}

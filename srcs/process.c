/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/11 12:21:25 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "map_utils.h"
#include "process.h"
#include "graphics.h"
#include <stdio.h>

void    awake(t_engine *eng)
{
	eng->ptr = mlx_init();
}

void    setup(t_engine *engine)
{
	t_map		*map;

	//WINDOW SETUP
	engine->win.size_x	= 1280;	//TODO PARSE
	engine->win.size_y	= 720;	//TODO PARSE
	if (!(engine->win.ptr = mlx_new_window(engine->ptr, engine->win.size_x, engine->win.size_y, __PROJECT_NAME)))
		return ;

	//SETUP FRAME IMAGE BUFFER INFO
	engine->buf.size = create_vector(engine->win.size_x, engine->win.size_y);
	
	//MAP SETUP
	map = create_map(10, 10);
	print_map(*map);

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

	draw_rect_to_buffer(&engine->buf, create_vector(1261, 700), create_vector(20, 20), 0xFFFFFF);
	
	mlx_put_image_to_window(engine->ptr, engine->win.ptr, engine->buf.img_ptr, 0, 0);
	return (0);
}

void    p_exit (t_engine *engine)
{
	free(engine->win.ptr);
	free(engine);
}

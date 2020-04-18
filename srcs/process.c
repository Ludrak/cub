/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/18 14:31:54 by coralie          ###   ########.fr       */
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
	//t_cast cast;
	
	//cast = perform_raycast(engine->player, engine->player.dir, engine->map);
	
	//printf ("dir : %f %f cast =>> x : %f, y : %f\n", engine->player.dir.x, engine->player.dir.y, cast.point.x, cast.point.y);
	//p_exit(engine);

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
		//if (engine->map.map[(int)floorf(engine->player.pos.x - cos(engine->player.rot + PI / 4) * engine->player.speed / 100)]
		//			[(int)floorf(engine->player.pos.x - cos(engine->player.rot + PI / 4) * engine->player.speed / 100)] != CUB_BLOCK)
					//{
        				engine->player.pos.x -= cos(engine->player.rot + PI / 4) * engine->player.speed / 100;
        				engine->player.pos.y -= sin(engine->player.rot + PI / 4) * engine->player.speed / 100;
					//}
    }
    if (engine->keys.down.pressed)
    {
		//if (engine->map.map[(int)floorf(engine->player.pos.x - cos(engine->player.rot + PI / 4) * engine->player.speed / 100)]
					//[(int)floorf(engine->player.pos.x - cos(engine->player.rot + PI / 4) * engine->player.speed / 100)] != CUB_BLOCK)
					//{
						engine->player.pos.x += cos(engine->player.rot + PI / 4) * engine->player.speed / 100;
						engine->player.pos.y += sin(engine->player.rot + PI / 4) * engine->player.speed / 100;
					//}
    }
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

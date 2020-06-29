/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 16:10:57 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"
#include <stdio.h>

void	awake(t_engine *eng)
{
	eng->ptr = mlx_init();
	if (!loadImages(eng))
		p_exit(eng, "Error while loading images.", STATUS_IMG_FAILED);
	register_cubes(eng);
	register_sprites(eng);
	/// !!!! PARSE MAP
	add_sprite(eng, 0, create_vector(2.5F, 2.5F), 0.5F);
	add_sprite(eng, 0, create_vector(2.5F, 3.5F), 0.5F);
}

void	setup(t_engine *engine)
{
	t_map		*map;
	int			map_fd;

	create_window(engine, 1280, 720, __PROJECT_NAME);
	init_camera(engine->win, &engine->camera, 80.0F);
	engine->player = create_player(create_vector(0, 0), 0, 6.0F);
	if ((map_fd = open("res/maps/map.cub", O_RDONLY)) > 0)
	{
		map = parse_map(map_fd, engine);
		engine->map = *map;
		printf("[MAP] Checking map bounds...\n");
		if (!check_map(engine->map) || (!engine->player.pos.x &&
			!engine->player.pos.y))
		{
			printf("[MAP] Error : INVALID MAP FORMAT\n");
			p_exit(engine, "Invalid map format.", STATUS_MAP_FAILED);
		}
		else
			printf("[MAP] Valid map format.\n");
		close(map_fd);
	}
	set_hooks(engine);
}

int		runtime(t_engine *engine)
{
	if (engine->keys.escape.pressed)
		p_exit(engine, "Escape key pressed", STATUS_SUCCESS);
	engine->buf.img_ptr = mlx_new_image(engine->ptr,
		engine->buf.size.x, engine->buf.size.y);
	engine->buf.data = (int *)mlx_get_data_addr(engine->buf.img_ptr,
		&engine->buf.bpp, &engine->buf.size_l, &engine->buf.endian);
	handle_input(engine);
	engine->camera.l_angle = engine->player.rot -
		radians(engine->camera.fov) / 2.0F;
	engine->camera.r_angle = engine->player.rot +
		radians(engine->camera.fov) / 2.0F;
	cast_to_frame_buffer(&engine->buf, engine);
	render_sprite(*engine, &engine->buf);
	draw_minimap(&engine->buf, *engine, create_vectorf(0, 0));
	mlx_put_image_to_window(engine->ptr, engine->win.ptr,
		engine->buf.img_ptr, 0, 0);
	mlx_destroy_image(engine->ptr, engine->buf.img_ptr);
	return (0);
}

void	p_exit(t_engine *engine, char *info_log, int status)
{
	t_list *free_tmp;

	printf("[EXIT]<REQUEST> : %s\n[EXIT] Clearing data...\n", info_log);
	if (status != STATUS_IMG_FAILED)
		mlx_destroy_window(engine->ptr, engine->win.ptr);
	destroy_camera(&engine->camera);
	while (engine->cubes->next && status != STATUS_IMG_FAILED)
	{
		free_tmp = engine->cubes->next;
		free(engine->cubes->content);
		free(engine->cubes);
		engine->cubes = free_tmp;
	}
	free(engine);
	printf("[EXIT] Done.");
	exit(0);
}

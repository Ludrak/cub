/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/11 14:31:11 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"
#include <stdio.h>

void	awake(t_engine *eng)
{
	eng->ptr = mlx_init();
	eng->buf.img_ptr = NULL;
	eng->loaded_textures = NULL;
	eng->sprites = NULL;
	eng->loaded_sprites = NULL;
	eng->animations = NULL;
	eng->format = 0;
	register_builtins(eng);
}

void	setup(t_engine *engine)
{
	parse_registry(engine, engine->map_file);
	if (!check_map(engine->map))
		p_exit(engine, "Invalid map.", STATUS_MAP_FAILED);
	set_hooks(engine);
}

int		runtime(t_engine *engine)
{
	engine->buf.img_ptr = mlx_new_image(engine->ptr,
		engine->buf.size.x, engine->buf.size.y);
	engine->buf.data = (int *)mlx_get_data_addr(engine->buf.img_ptr,
		&engine->buf.bpp, &engine->buf.sl, &engine->buf.endian);
	handle_input(engine);
	update_player(&engine->player, engine->map);
	engine->cam.l_angle = engine->player.rot -
		rad(engine->cam.fov) / 2.0F;
	engine->cam.r_angle = engine->player.rot +
		rad(engine->cam.fov) / 2.0F;
	cast_to_frame_buffer(&engine->buf, engine);
	render_sprite(*engine, &engine->buf);
	if (engine->keys.take_screenshot.pressed || engine->first_screen)
		take_screenshot(engine);
	if (engine->keys.show_map.pressed && engine->format == CUSTOM_F)
		draw_minimap(&engine->buf, *engine, create_vectorf(0, 0));
	mlx_put_image_to_window(engine->ptr, engine->win.ptr,
		engine->buf.img_ptr, 0, 0);
	mlx_destroy_image(engine->ptr, engine->buf.img_ptr);
	engine->buf.img_ptr = NULL;
	return (0);
}

void	p_exit(t_engine *engine, char *info_log, int status)
{
	if (status != STATUS_SUCCESS && status != STATUS_WINDOW_CLOSED)
		ft_printf("Error\n");
	ft_printf("[EXIT]: %s\n[EXIT] Clearing data...\n", info_log);
	unload_textures(engine);
	if (engine->allocs & CREATED_WIN)
	{
		ft_printf("[MLX] Destroying window data.\n");
		mlx_destroy_window(engine->ptr, engine->win.ptr);
	}
	if (engine->allocs & CREATED_CAM)
		destroy_camera(&engine->cam);
	if (engine->allocs & CREATED_CUBES)
		unload_cubes(engine);
	if (engine->allocs & CREATED_SPRITE)
		unload_sprites(engine);
	if (engine->allocs & CREATED_MAP)
		unload_map(engine);
	print_exit_status(status);
	free(engine->ptr);
	free(engine);
	exit(0);
}

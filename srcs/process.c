/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/06 17:15:42 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"
#include <stdio.h>

void	awake(t_engine *eng)
{
	eng->ptr = mlx_init();
	if (!load_images(eng))
		p_exit(eng, "Error while loading images.", STATUS_IMG_FAILED);
	eng->sprites = NULL;
	eng->loaded_sprites = NULL;
	eng->animations = NULL;
	register_builtins(eng);
}

void	setup(t_engine *engine)
{
	parse_registry(engine, "res/maps/map.cmap");
	if (!check_map(engine->map))
		p_exit (engine, "Invalid map.", STATUS_MAP_FAILED);
	/*t_anim *anim = create_animation(engine, 20.0F);
	add_animation_frame(anim, (t_image *)engine->loaded_textures->content);
	add_animation_frame(anim, (t_image *)engine->loaded_textures->next->content);
	add_animation_frame(anim, (t_image *)engine->loaded_textures->next->next->content);
	set_anim_ptr(anim, (t_image **)&((t_cube *)(engine->cubes->content))->tex);*/
	set_hooks(engine);
}

int		runtime(t_engine *engine)
{
	engine->buf.img_ptr = mlx_new_image(engine->ptr,
		engine->buf.size.x, engine->buf.size.y);
	engine->buf.data = (int *)mlx_get_data_addr(engine->buf.img_ptr,
		&engine->buf.bpp, &engine->buf.sl, &engine->buf.endian);
	handle_input(engine);
	engine->cam.l_angle = engine->player.rot -
		rad(engine->cam.fov) / 2.0F;
	engine->cam.r_angle = engine->player.rot +
		rad(engine->cam.fov) / 2.0F;
	cast_to_frame_buffer(&engine->buf, engine);
	render_sprite(*engine, &engine->buf);
	if (engine->keys.show_map.pressed && engine->format == CUSTOM_F)
		draw_minimap(&engine->buf, *engine, create_vectorf(0, 0));
	mlx_put_image_to_window(engine->ptr, engine->win.ptr,
		engine->buf.img_ptr, 0, 0);
	mlx_destroy_image(engine->ptr, engine->buf.img_ptr);
	return (0);
}

void	p_exit(t_engine *engine, char *info_log, int status)
{
	printf("[EXIT]<REQUEST> : %s\n[EXIT] Clearing data...\n", info_log);
	if (engine->allocs & CREATED_WIN)
		mlx_destroy_window(engine->ptr, engine->win.ptr);
	if (engine->allocs & CREATED_CAM)
		destroy_camera(&engine->cam);
	unload_textures(engine);
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

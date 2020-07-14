/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:19:30 by coralie           #+#    #+#             */
/*   Updated: 2020/07/11 02:05:22 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <X11/keysym.h>

int				key_pressed_event(int key, void *engine_ptr)
{
	t_engine	*engine;

	engine = engine_ptr;
	if (key == engine->keys.l_cam.value)
		engine->keys.l_cam.pressed = 1;
	if (key == engine->keys.r_cam.value)
		engine->keys.r_cam.pressed = 1;
	if (key == engine->keys.up.value)
		engine->keys.up.pressed = 1;
	if (key == engine->keys.down.value)
		engine->keys.down.pressed = 1;
	if (key == engine->keys.left.value)
		engine->keys.left.pressed = 1;
	if (key == engine->keys.right.value)
		engine->keys.right.pressed = 1;
	if (key == engine->keys.escape.value)
		engine->keys.escape.pressed = 1;
	if (key == engine->keys.show_map.value)
		engine->keys.show_map.pressed = 1;
	if (key == engine->keys.take_screenshot.value)
		engine->keys.take_screenshot.pressed = 1;
	return (key);
}

int				key_released_event(int key, void *engine_ptr)
{
	t_engine	*engine;

	engine = engine_ptr;
	if (key == engine->keys.l_cam.value)
		engine->keys.l_cam.pressed = 0;
	if (key == engine->keys.r_cam.value)
		engine->keys.r_cam.pressed = 0;
	if (key == engine->keys.up.value)
		engine->keys.up.pressed = 0;
	if (key == engine->keys.down.value)
		engine->keys.down.pressed = 0;
	if (key == engine->keys.left.value)
		engine->keys.left.pressed = 0;
	if (key == engine->keys.right.value)
		engine->keys.right.pressed = 0;
	if (key == engine->keys.escape.value)
		engine->keys.escape.pressed = 0;
	if (key == engine->keys.show_map.value)
		engine->keys.show_map.pressed = 0;
	if (key == engine->keys.take_screenshot.value)
		engine->keys.take_screenshot.pressed = 0;
	return (key);
}

t_control_keys	set_key_values(void)
{
	t_control_keys	keys;

	keys.up.value = XK_w;
	keys.down.value = XK_s;
	keys.left.value = XK_d;
	keys.right.value = XK_a;
	keys.escape.value = XK_Escape;
	keys.show_map.value = XK_m;
	keys.take_screenshot.value = XK_F2;
	keys.l_cam.value = XK_Left;
	keys.r_cam.value = XK_Right;
	keys.up.pressed = 0;
	keys.down.pressed = 0;
	keys.left.pressed = 0;
	keys.right.pressed = 0;
	keys.escape.pressed = 0;
	keys.show_map.pressed = 0;
	keys.take_screenshot.pressed = 0;
	keys.l_cam.pressed = 0;
	keys.r_cam.pressed = 0;
	return (keys);
}

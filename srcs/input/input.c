/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:19:30 by coralie           #+#    #+#             */
/*   Updated: 2020/07/06 14:08:30 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <X11/keysym.h>

int				key_pressed_event(int key, void *engine_ptr)
{
	t_engine	*engine;

	engine = engine_ptr;
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
	return (key);
}

int				key_released_event(int key, void *engine_ptr)
{
	t_engine	*engine;

	engine = engine_ptr;
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
	return (key);
}

t_control_keys	set_key_values(void)
{
	t_control_keys	keys;

	keys.up.value = XK_Up;
	keys.down.value = XK_Down;
	keys.left.value = XK_Left;
	keys.right.value = XK_Right;
	keys.escape.value = XK_Escape;
	keys.show_map.value = XK_m;
	keys.up.pressed = 0;
	keys.down.pressed = 0;
	keys.left.pressed = 0;
	keys.right.pressed = 0;
	keys.escape.pressed = 0;
	keys.show_map.pressed = 0;
	return (keys);
}

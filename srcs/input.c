/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:19:30 by coralie           #+#    #+#             */
/*   Updated: 2020/04/19 21:35:42 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int     key_pressed_event(int key, void *engine_ptr)
{
    t_engine    *engine;
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
    return (0);
}

int     key_released_event(int key, void *engine_ptr)
{
    t_engine    *engine;
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
    return (0);
}

t_control_keys    set_key_values()
{
    t_control_keys  keys;
    keys.up.value       = 126;
    keys.down.value     = 125;
    keys.left.value     = 123;
    keys.right.value    = 124;
    keys.escape.value   = 53;
    keys.up.pressed       = 0;
    keys.down.pressed     = 0;
    keys.left.pressed     = 0;
    keys.right.pressed    = 0;
    keys.escape.pressed   = 0;
    return (keys);    
}
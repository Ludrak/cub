/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:43:00 by lrobino           #+#    #+#             */
/*   Updated: 2020/05/19 21:35:36 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

#include "engine.h"

typedef struct  s_sprite
{
    t_image     *sprite;
    t_vec2d     pos;

    //bounded [0;1] 1 means cub height
    float       size;
    float       height;
}               t_sprite;

void render_sprite(t_engine eng, t_image *buf);

#endif
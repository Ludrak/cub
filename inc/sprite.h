/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:43:00 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 16:10:29 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

#include "engine.h"

typedef struct  s_spt_info
{
    float		spt_angle;
	float		spt_size;
	float		spt_height;
}               t_spt_info;

typedef struct  s_sprite
{
    t_image     sprite;
    t_vec2d     pos;
    int         id;

    //bounded [0;1] 1 means cub height
    float       dist;
    float       size;
    float       height;
    float       start_x;
    float       end_x;
}               t_sprite;

void        render_sprite(t_engine eng, t_image *buf);
t_spt_info	create_spt_info(t_engine eng, t_sprite tmp);
int         register_sprite(t_engine *eng, char *texture, int sprite_id);
int			add_sprite(t_engine *eng, int sprite_id, t_vec2d pos, float size);
t_sprite    *get_sprite_by_id(t_engine *eng, int id);

#endif
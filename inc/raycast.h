/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:14:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/20 19:36:37 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "engine.h"

/*
**  BLOCKS FACES
*/
# define NONE -1
# define LEFT 0
# define RIGHT 1
# define TOP 2
# define BOTTOM 3

typedef uint8_t t_face;

typedef struct  s_cast
{
    float   dist;
    t_vec2d point;
    t_face  face;
    float   face_pos;
}               t_cast;

typedef struct  s_ray
{
    t_vec2d start;
    t_vec2d end;
}               t_ray;

t_cast      perform_raycast(t_vec2d pos, t_vec2d r_dir, t_map map);
void        cast_to_frame_buffer(t_image *buffer, t_engine engine);

/**
 *      UTILS 
 */
t_cast      create_cast_info(t_vec2d point, t_vec2d cast_block, t_vec2d dir);
t_ray       create_ray (t_vec2d start, t_vec2d end);
float       ft_map(float value, float min1, float max1, float min2, float max2);

#endif
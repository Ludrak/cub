/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:14:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 16:04:15 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "engine.h"

# define F_NORTH    0
# define F_SOUTH    1
# define F_EAST     2
# define F_WEST     3

typedef uint8_t t_face;

typedef struct  s_cast
{
    float   dist;
    t_vec2d point;
    t_face  face;
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
t_ray       create_ray (t_vec2d start, t_vec2d end);
float       ft_map(float value, float min1, float max1, float min2, float max2);

#endif
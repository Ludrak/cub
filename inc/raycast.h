/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:14:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 18:31:49 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "engine.h"

/*
**  BLOCKS FACES
*/
# define NONE 0
# define LEFT 1
# define RIGHT 2
# define TOP 3
# define BOTTOM 4


//void		draw_ray_to_buffer(t_engine *eng, int x, int h, t_image tex, float offset, t_vec2d p_dir, float scale_f)

typedef struct  s_ray
{
    t_vec2d start;
    t_vec2d end;
}               t_ray;

t_cast      perform_raycast(t_engine *eng, t_vec2d pos, t_vec2d r_dir, t_map map);
void        cast_to_frame_buffer(t_image *buffer, t_engine *engine);

/**
 *      UTILS 
 */
t_cast      create_cast_info(t_cube *cube, t_vec2d point, t_vec2d cast_block);
t_ray       create_ray (t_vec2d start, t_vec2d end);
float       ft_map(float value, float min1, float max1, float min2, float max2);

#endif
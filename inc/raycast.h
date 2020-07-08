/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:14:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/07 20:01:47 by lrobino          ###   ########.fr       */
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
float       ft_map(float value, t_vec2f range1, t_vec2f range2);
#endif
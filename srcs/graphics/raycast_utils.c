/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:38:11 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 13:39:48 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_ray       create_ray (t_vec2d start, t_vec2d end)
{
    t_ray   ray;
    ray.start = start;
    ray.end = end;
    return (ray);
}

static t_face	get_face (t_vec2d cast_block)
{
	if (fabs(cast_block.x - 0.5f) > fabs(cast_block.y - 0.5f))
	{
		if (cast_block.x <= 0.0001f)		
			return (LEFT);
		else if (cast_block.x >= 0.9999f)
			return (RIGHT);
	}
	else
	{
		if(cast_block.y >= 0.9999f)
			return (TOP);
		else
			return (BOTTOM);
	}
	return (NONE);
}

t_cast      create_cast_info(t_cube *cube, t_vec2d point, t_vec2d cast_block)
{
    t_cast			cast;
	cast.point = point;
	cast.cube = cube;
	cast.face = get_face(cast_block);
	if (cast.face != NONE)
	{
		if (cast.face == BOTTOM || cast.face == TOP)
			cast.face_pos = cast_block.x;
		else
			cast.face_pos = cast_block.y;
	}
	return (cast);
}

float ft_map(float value, float min1, float max1, float min2, float max2)
{
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}
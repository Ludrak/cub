/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:38:11 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/20 19:57:42 by lrobino          ###   ########.fr       */
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

t_cast      create_cast_info(t_vec2d point, t_vec2d cast_block, t_vec2d dir)
{
    t_cast			cast;
	t_face			face;
	(void)dir;
	face = -1;
	cast.point = point;

	if (fabs(cast_block.x - 0.5f) > fabs(cast_block.y - 0.5f))
	{
		if (cast_block.x <= 0.0001)
		{			
			face = LEFT;
			cast.face_pos = cast_block.y;
		}
		else if (cast_block.x >= 0.9999)
		{
			face = RIGHT;
			cast.face_pos = cast_block.y;
		}
	}
	else
	{
		if(cast_block.y >= 0.9999f)
		{
			face = TOP;
			cast.face_pos = cast_block.x;
		}
		else
		{
			face = BOTTOM;
			cast.face_pos = cast_block.x;
		}
	}

	cast.face = face;
	return (cast);
}

float ft_map(float value, float min1, float max1, float min2, float max2)
{
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}
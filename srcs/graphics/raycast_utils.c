/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:38:11 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/07 20:04:12 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_ray			create_ray(t_vec2d start, t_vec2d end)
{
	t_ray	ray;

	ray.start = start;
	ray.end = end;
	return (ray);
}

static t_face	get_face(t_vec2d cast_block)
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
		if (cast_block.y >= 0.9999f)
			return (TOP);
		else
			return (BOTTOM);
	}
	return (NONE);
}

t_cast			create_cast_info
	(t_cube *cube, t_vec2d point, t_vec2d cast_block)
{
	t_cast	cast;

	cast.point = point;
	cast.cube = cube;
	cast.face = get_face(cast_block);
	cast.tex = cube->tex[cast.face];
	if (cast.face != NONE)
	{
		if (cast.face == BOTTOM || cast.face == TOP)
			cast.face_pos = cast_block.x;
		else
			cast.face_pos = cast_block.y;
	}
	return (cast);
}

float			ft_map
	(float value, t_vec2f range1, t_vec2f range2)
{
	return (range2.x + (value - range1.x) *
		(range2.y - range2.x) / (range1.y - range1.x));
}

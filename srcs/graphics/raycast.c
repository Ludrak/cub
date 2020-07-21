/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 15:50:28 by coralie           #+#    #+#             */
/*   Updated: 2020/07/21 17:40:47 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_vec2d			get_sqinter(t_vec2d pos, t_vec2d dir)
{
	t_vec2d inter;
	t_vec2d t;

	inter = create_vector(-1, -1);
	t = create_vector(0, 0);
	if ((pos.x < 0) || (pos.x > 1) || (pos.y < 0) || (pos.y > 1)
		|| (dir.x == 0 && dir.y == 0))
		return (create_vector(0, 0));
	if (dir.x > 0 && (inter.x = RIGHT))
		t.x = (1 - pos.x) / dir.x;
	else if (dir.x < 0 && (inter.x = LEFT))
		t.x = (-pos.x) / dir.x;
	if (dir.y > 0 && (inter.y = TOP))
		t.y = (1 - pos.y) / dir.y;
	else if (dir.y < 0 && (inter.y = BOTTOM))
		t.y = (-pos.y) / dir.y;
	if (inter.x == -1 && inter.y == -1)
		return (create_vector(0, 0));
	else if (inter.x == -1 || inter.y == -1)
		return (create_vector(pos.x +
			(inter.x == -1 ? t.y : t.x) * dir.x, pos.y + t.y * dir.y));
	else if (t.x > t.y)
		return (create_vector(pos.x + t.y * dir.x, pos.y + t.y * dir.y));
	else
		return (create_vector(pos.x + t.x * dir.x, pos.y + t.x * dir.y));
}

/*
**	vec[0] = real position vector
**	vec[1] = cast position vector
**	vec[2] = direction
*/

static t_cast	do_next_cast(t_engine *eng, t_vec2d vec[3], t_map map)
{
	if (map.map[(int)(vec[0].x) - ((vec[1].x == 0) ? 1 : 0)]
				[(int)(vec[0].y - ((vec[1].y == 0) ? 1 : 0))]->id != CUB_AIR)
	{
		return (create_cast_info(
		map.map[(int)(vec[0].x) - ((vec[1].x == 0) ? 1 : 0)]
			[(int)(vec[0].y - ((vec[1].y == 0) ? 1 : 0))],
		vec[0], vec[1]));
	}
	return (perform_raycast(eng, vec[0], vec[2], map));
}

t_cast			perform_raycast
	(t_engine *eng, t_vec2d pos, t_vec2d dir, t_map map)
{
	t_vec2d cast;
	t_vec2d real;
	t_vec2d g_pos;
	t_vec2d r_pos;

	g_pos = create_vector((int)(pos.x), (int)(pos.y));
	r_pos = vec_sub(pos, g_pos);
	if (r_pos.x == 0.0f && dir.x < 0.0f && (r_pos.x = 1.0F))
		g_pos.x -= 1.0f;
	if (r_pos.y == 0.0f && dir.y < 0.0f && (r_pos.y = 1.0F))
		g_pos.y -= 1.0f;
	if (is_on_map(map, g_pos.x, g_pos.y))
	{
		cast = get_sqinter(r_pos, dir);
		real = create_vector(g_pos.x + cast.x, g_pos.y + cast.y);
		if (map.map[(int)g_pos.x][(int)g_pos.y]->id != CUB_AIR)
			return (create_cast_info(map.map[(int)g_pos.x][(int)g_pos.y],
			pos, create_vector(pos.x - (int)pos.x, pos.y - (int)pos.y)));
		else if (is_on_map(map, real.x, real.y))
			return (do_next_cast(eng, (t_vec2d[3]){real, cast, dir}, map));
	}
	return (create_cast_info(NULL, create_vector(0, 0), create_vector(0, 0)));
}

void			cast_to_frame_buffer(t_image *buffer, t_engine *engine)
{
	int		i;
	float	angle;
	float	a;
	t_cast	cast;
	t_vec2d	r_dir;

	angle = rad(engine->cam.fov) / (float)buffer->size.x;
	a = -rad(engine->cam.fov / 2.0F);
	i = 0;
	while (a <= rad(engine->cam.fov / 2.0F)
		&& i < engine->buf.size.x - 1)
	{
		r_dir.x = cosf(engine->player.rot + a);
		r_dir.y = sinf(engine->player.rot + a);
		cast = perform_raycast(engine, engine->player.pos, r_dir, engine->map);
		cast.point = vec_sub(cast.point, engine->player.pos);
		engine->cam.z_buffer[i] = vec_mag(cast.point);
		cast.wall_h = engine->win.size_y / (cosf(a) * engine->cam.z_buffer[i]);
		cast.scale_f = cosf(a);
		if (cast.cube)
			draw_ray_to_buffer(engine, i, cast);
		i++;
		a += angle;
	}
}

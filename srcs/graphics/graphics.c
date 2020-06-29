/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:26:17 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 22:25:36 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		draw_line_to_buffer(t_image *buff, int x, int h, t_color color)
{
	int	start;

	if (h > buff->size.y)
		h = buff->size.y;
	start = buff->size.y / 2 - h / 2;
	while (h-- > 0 &&
		x + (++start * (int)buff->size.x) < buff->size.x * buff->size.y)
	{
		buff->data[x + (start * (int)buff->size.x)] = color.value;
	}
}

static void	draw_floor(t_engine *eng, int x, int y, t_cast cast)
{
	t_vec2d		dir;
	t_vec2d		cast_v;
	t_vec2d		r_pos;
	t_vec2i		t;
	float		dir_z;

	dir.y = sin(eng->player.rot + PI + (ft_map(x, 0, eng->buf.size.x,
		-radians(eng->camera.fov) / 2, radians(eng->camera.fov) / 2)));
	dir.x = cos(eng->player.rot + PI + (ft_map(x, 0, eng->buf.size.x,
		-radians(eng->camera.fov) / 2, radians(eng->camera.fov) / 2)));
	r_pos = eng->player.pos;
	while (y < eng->buf.size.y - 1)
	{
		dir_z = sin(PI + ft_map(y, 0, eng->buf.size.y, -0.5f, 0.5f))
			* cast.scale_f;
		cast_v = create_vector(dir.x * ((1.0F - eng->camera.height) / dir_z)
			+ r_pos.x, dir.y * ((1.0F - eng->camera.height) / dir_z) + r_pos.y);
		t.x = (int)((cast_v.x - floor(cast_v.x)) * (cast.cube->tex.size.x));
		t.y = (int)((cast_v.y - floor(cast_v.y)) * (cast.cube->tex.size.y));
		eng->buf.data[x + (y * (int)eng->buf.size.x)] = eng->cub_tex_floor.data
			[(int)(cast.cube->tex.size.x * t.x + t.y)];
		eng->buf.data[x + ((eng->buf.size.y - y++) * (int)eng->buf.size.x)] =
			eng->cub_tex_ceil.data[(int)(cast.cube->tex.size.x * t.x + t.y)];
	}
}

void		draw_ray_to_buffer(t_engine *eng, int x, t_cast cast)
{
	int		y;
	int		start_h;
	int		h_offset;
	int		i;
	int		pos;

	i = 0;
	h_offset = 0;
	if (cast.wall_h > eng->buf.size.y &&
		(h_offset = (cast.wall_h - eng->buf.size.y) / 2))
		cast.wall_h = eng->buf.size.y;
	start_h = cast.wall_h;
	y = (eng->buf.size.y * eng->camera.height) - cast.wall_h / 2;
	while (cast.wall_h-- > 0 && x +
		(++y * (int)eng->buf.size.x) < eng->buf.size.x * eng->buf.size.y)
	{
		pos = (int)ft_map(cast.face_pos, 0, 1, 0,
		cast.cube->tex.size.x) + (int)ft_map(i, -h_offset, start_h + h_offset,
		0, cast.cube->tex.size.y) * cast.cube->tex.size.x;
		if (pos < cast.cube->tex.size.x * cast.cube->tex.size.y)
			eng->buf.data[x + (y * (int)eng->buf.size.x)] =
				cast.cube->tex.data[pos];
		i++;
	}
	draw_floor(eng, x, y, cast);
}

void		draw_rect_to_buffer
	(t_image *buff, t_vec2f pos, t_vec2f size, t_color color)
{
	int buffer_pos;
	int i;

	if (pos.x < 0 || pos.y < 0 || pos.x > buff->size.x || pos.y > buff->size.y
	|| pos.x + size.x > buff->size.x || pos.y + size.x > buff->size.y)
	{
		return ;
	}
	buffer_pos = pos.y * buff->size.x + pos.x;
	while (size.y)
	{
		i = 0;
		while (i < size.x)
			buff->data[buffer_pos + i++] = color.value;
		buffer_pos += buff->size.x;
		size.y--;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:26:17 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/03 14:29:28 by lrobino          ###   ########lyon.fr   */
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

static void	draw_floor_color(t_engine *eng, int x, int y)
{
	while (y < eng->buf.size.y - 1)
	{
		eng->buf.data[x + (y * (int)eng->buf.size.x)] = eng->floor_col.value;
		eng->buf.data[x + ((eng->buf.size.y - y++) * (int)eng->buf.size.x)] =
			eng->ceil_col.value;
	}
}

static void	draw_floor(t_engine *eng, int x, int y, t_cast cast)
{
	t_vec2d		dir;
	t_vec2d		cast_v;
	t_vec2d		r_pos;
	t_vec2i		t;
	float		dir_z;

	dir.y = eng->player.rot + PI + (ft_map(x, vec2f(0, eng->buf.size.x),
		vec2f(-rad(eng->cam.fov) / 2, rad(eng->cam.fov) / 2)));
	dir.x = cos(dir.y);
	dir.y = sin(dir.y);
	r_pos = eng->player.pos;
	while (y < eng->buf.size.y - 1)
	{
		dir_z = sin(PI + ft_map(y, create_vectorf(0, eng->buf.size.y),
			create_vectorf(-0.5f, 0.5f))) * cast.scale_f;
		cast_v = create_vector(dir.x * ((1.0F - eng->cam.height) / dir_z)
			+ r_pos.x, dir.y * ((1.0F - eng->cam.height) / dir_z) + r_pos.y);
		t.x = (int)((cast_v.x - floor(cast_v.x)) * (cast.tex->size.x));
		t.y = (int)((cast_v.y - floor(cast_v.y)) * (cast.tex->size.y));
		eng->buf.data[x + (y * (int)eng->buf.size.x)] = eng->cub_tex_floor->data
			[(int)(cast.tex->size.x * t.x + t.y)];
		eng->buf.data[x + ((eng->buf.size.y - y++) * (int)eng->buf.size.x)] =
			eng->cub_tex_ceil->data[(int)(cast.tex->size.x * t.x + t.y)];
	}
}

void		draw_ray_to_buffer(t_engine *eng, int x, t_cast cast)
{
	int		y;
	int		pos;
	double	i;
	double	offset;
	double	clip_offset;

	clip_offset = (cast.wall_h <= eng->buf.size.y) ? 0 :
		(cast.wall_h - (float)eng->buf.size.y) *
		cast.tex->size.y / cast.wall_h;
	offset = (double)(cast.tex->size.y) / cast.wall_h;
	if (clip_offset != 0)
		cast.wall_h = eng->buf.size.y;
	i = clip_offset / 2.0F;
	y = eng->buf.size.y / 2 - cast.wall_h / 2;
	while (cast.wall_h-- > 0 && y < eng->buf.size.y)
	{
		pos = (cast.face_pos * (double)cast.tex->size.x)
			+ (((int)(i += offset)) * (double)cast.tex->size.y);
		if (pos >= 0 && pos < cast.tex->size.x * cast.tex->size.y)
			eng->buf.data[x + (y++ * (int)eng->buf.size.x)] =
				cast.tex->data[pos];
	}
	(eng->format == FORMAT) ? draw_floor_color(eng, x, y)
		: draw_floor(eng, x, y, cast);
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

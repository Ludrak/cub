/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:53:05 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 15:54:12 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		draw_sprite_to_buf(t_engine eng, t_vec2f pos, t_vec2f size,
	t_sprite sprite)
{
	int	i;
	int j;
	int buffer_pos;

	j = 0;
	buffer_pos = pos.y * eng.buf.size.x + pos.x;
	while (j < size.y)
	{
		i = sprite.start_x;
		while (i < sprite.end_x)
		{
			if (i + pos.x > 0 && i + pos.x < eng.buf.size.x && sprite.dist <
				eng.camera.z_buffer[(int)(i + pos.x)] &&
				sprite.sprite.data[(int)((int)((float)j / size.y *
				sprite.sprite.size.y) * sprite.sprite.size.x +
				(i / size.x * sprite.sprite.size.x))] != 0x0)
				eng.buf.data[buffer_pos + i] = sprite.sprite.data
				[(int)((int)((float)j / size.y * sprite.sprite.size.y)
				* sprite.sprite.size.x +
				(i / size.x * sprite.sprite.size.x))];
			i++;
		}
		j++;
		buffer_pos += eng.buf.size.x;
	}
}

void		draw_sprite(t_engine eng, t_vec2f pos, t_vec2f size,
				t_sprite sprite)
{
	sprite.start_x = 0;
	sprite.end_x = size.x;
	if (pos.x + size.x < 0 || pos.y < 0 || pos.x > eng.buf.size.x
		|| pos.y > eng.buf.size.y || pos.y + size.y > eng.buf.size.y)
		return ;
	if (pos.x < 0)
		sprite.start_x = -pos.x;
	else if (pos.x + size.x > eng.buf.size.x)
		sprite.end_x = eng.buf.size.x - pos.x;
	draw_sprite_to_buf(eng, pos, size, sprite);
}

void		render_sprite(t_engine eng, t_image *buf)
{
	t_sprite	*spt;
	t_sprite	tmp;
	t_spt_info	info;

	//ft_lstsort eng.sprites
	while (eng.sprites)
	{
		spt = (t_sprite *)eng.sprites->content;
		tmp = *spt;
		tmp.pos = vec_sub(tmp.pos, eng.player.pos);
		tmp.dist = vec_mag(tmp.pos);
		info = create_spt_info(eng, tmp);
		draw_sprite(eng, create_vectorf(
			ft_map(info.spt_angle, eng.camera.l_angle,
			eng.camera.r_angle, 0, buf->size.x) -
			(int)(info.spt_size / 2.0F), eng.buf.size.y / 2 -
			(int)(info.spt_size / 2.0F) + info.spt_height),
			create_vectorf((int)info.spt_size, (int)info.spt_size), tmp);
		eng.sprites = eng.sprites->next;
	}
}

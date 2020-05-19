/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 21:53:05 by lrobino           #+#    #+#             */
/*   Updated: 2020/05/19 22:14:28 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

void        draw_sprite(t_image *buff, t_vec2f pos, t_vec2f size, t_image sprite)
{
    (void) sprite;
    int buffer_pos;
    int i;

    if (pos.x + size.x < 0 || pos.y < 0 || pos.x > buff->size.x || pos.y > buff->size.y || pos.y + size.y > buff->size.y)
        return ;
    if (pos.x < 0)
    {
        size.x += pos.x;
        pos.x = 0;
    }
    else if (pos.x + size.x > buff->size.x)
        size.x = buff->size.x - pos.x;

    buffer_pos = pos.y * buff->size.x + pos.x;
    while (size.y)
    {
        i = 0;
        while (i < size.x)
        {
            if (i + pos.x > 0 || i + pos.x < buff->size.x)
                buff->data[buffer_pos + i] = 0x00FF00;
            i++;
        }
             
        buffer_pos += buff->size.x;
        size.y--;
    }
}

void render_sprite(t_engine eng, t_image *buf)
{
    t_sprite spt;
    spt.pos = create_vector(2.5f, 2.5f);
    spt.sprite = &eng.cub_tex_ceil;
    spt.size = 0.3F;
    spt.height = 0.3f;


    spt.pos = vec_sub(spt.pos, eng.player.pos);
    float sprite_angle = atan2f(spt.pos.y, spt.pos.x);
    if (sprite_angle < 0)
        sprite_angle += TWO_PI;
    float left_screen = eng.player.rot - radians(eng.player.fov) / 2.0F;
    float right_screen = eng.player.rot + radians(eng.player.fov) / 2.0F;
    float sp_xpos = ft_map(sprite_angle, left_screen, right_screen, 0, buf->size.x);

    float spt_size = (spt.size * VIEW_HEIGHT) / vec_mag(spt.pos);
    float spt_height = (int)((1 - spt.height - 0.5F) * (VIEW_HEIGHT / 2) / vec_mag(spt.pos));
    
    draw_sprite(buf, create_vectorf(sp_xpos - (int)(spt_size / 2.0F), eng.buf.size.y / 2 - (int)(spt_size / 2.0F) + spt_height), create_vectorf((int)spt_size, (int)spt_size), eng.cub_tex_floor);
}
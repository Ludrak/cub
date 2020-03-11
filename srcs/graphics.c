/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:26:17 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/11 12:18:21 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void        draw_line_to_buffer(t_image *buff, int x, int h)
{
    (void)buff;
    (void)x;
    (void)h;
}

void        draw_rect_to_buffer(t_image *buff, t_vec2d pos, t_vec2d size, int color)
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
           buff->data[buffer_pos + i++] = color;
             
        buffer_pos += buff->size.x;
        size.y--;
    }
}
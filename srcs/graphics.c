/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:26:17 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/21 10:48:29 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void        draw_line_to_buffer(t_image *buff, int x, int h, t_color color)
{
    int     start;
    
    if (h > buff->size.y)
        h = buff->size.y;
    start = buff->size.y / 2 - h / 2;
    while (h-- > 0 && x + (++start * (int)buff->size.x) < buff->size.x * buff->size.y)
    {
        buff->data[x + (start * (int)buff->size.x)] = color.value;
    }
}

void        draw_rect_to_buffer(t_image *buff, t_vec2f pos, t_vec2f size, t_color color)
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

static int load_from_png(char *png, t_image *img, t_engine engine)
{
    if (!png || !img)   
        return (0);
    img->img_ptr = mlx_png_file_to_image(engine.ptr, png, &img->size.x, &img->size.y);
    img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
    return (1);
}

int    loadImages(t_engine *engine)
{
    if (!load_from_png("cub_left.png", &engine->cub_tex_left, *engine))
        return (0);
    if (!load_from_png("cub_right.png", &engine->cub_tex_right, *engine))
        return (0);
    if (!load_from_png("cub_top.png", &engine->cub_tex_top, *engine))
        return (0);
    if (!load_from_png("cub_bottom.png", &engine->cub_tex_bottom, *engine))
        return (0);
    return (1);
}
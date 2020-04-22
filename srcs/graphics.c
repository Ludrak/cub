/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:26:17 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/22 14:11:52 by lrobino          ###   ########.fr       */
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

void        draw_ray_to_buffer(t_engine *eng, int x, int h, t_image tex, float offset)
{
    int     start;
    int     start_h;
    int     h_offset;
    int     i;
    int     pos;

    int dist;
    
    i = 0;
    h_offset = 0;
    if (h > eng->buf.size.y)
    {
        h_offset = (h - eng->buf.size.y) / 2;
        h = eng->buf.size.y;
    }
    start_h = h;
    dist = ft_map(h, 0, eng->buf.size.y, 20, 0);


    start = eng->buf.size.y / 2 + 50 - h / 2;
    while (h-- > 0 && x + (++start * (int)eng->buf.size.x) < eng->buf.size.x * eng->buf.size.y)
    {
        pos = (int)ft_map(offset, 0, 1, 0, tex.size.x) + (int)ft_map(i, -h_offset, start_h + h_offset, 0, tex.size.y) * tex.size.x;
#ifdef  HIGH_GRAPHICS
        t_color col;
        col = set_color(tex.data[pos]);
        col.channel.r = ft_constrain(col.channel.r - dist, 0, 255);
        col.channel.g = ft_constrain(col.channel.g - dist, 0, 255);
        col.channel.b = ft_constrain(col.channel.b - dist, 0, 255);
        if (pos < eng->buf.size.x * eng->buf.size.y)
        { 
            eng->buf.data[x + (start * (int)eng->buf.size.x)] = col.value;
        }
#else
        if (pos < eng->buf.size.x * eng->buf.size.y)
        { 
            eng->buf.data[x + (start * (int)eng->buf.size.x)] = tex.data[pos];
        }
#endif
        i++;
    }
    while (start < eng->buf.size.y - 1)
    {
#ifdef  HIGH_GRAPHICS
        float floorX;
        float floorY;
        floorX = eng->player.pos.x + ((0.5f * eng->buf.size.y) / (eng->player.pos.y - eng->buf.size.y / 2)) * (sin(eng->player.rot) - (-cos(eng->player.rot)));
        floorY = eng->player.pos.y + ((0.5f * eng->buf.size.y) / (eng->player.pos.y - eng->buf.size.y / 2)) * (cos(eng->player.rot) - (sin(eng->player.rot)));
        
        floorX += ((0.5f * eng->buf.size.y) / (eng->player.pos.y - eng->buf.size.y / 2)) * ((sin(eng->player.rot) + (-cos(eng->player.rot))) - ((sin(eng->player.rot) - (-cos(eng->player.rot)) / eng->buf.size.x))) * x;
        floorY += ((0.5f * eng->buf.size.y) / (eng->player.pos.y - eng->buf.size.y / 2)) * ((cos(eng->player.rot) + (sin(eng->player.rot))) - ((cos(eng->player.rot) - (sin(eng->player.rot)) / eng->buf.size.y))) * start;
        
        float tx;
        float ty;
        tx = (int)(tex.size.x * (floorX - (int)floorX)) & (tex.size.x - 1);
        ty = (int)(tex.size.y * (floorY - (int)floorY)) & (tex.size.y - 1);
        eng->buf.data[x + (start++ * (int)eng->buf.size.x)] = tex.data[(int)(tex.size.x * ty + tx)];
#endif
        start++;
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
    (void)engine;//TODO
    if (!(img->img_ptr = mlx_png_file_to_image(engine.ptr, png, &img->size.x, &img->size.y)))
        return (0);
    if (!(img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian)))
        return (0);
    return (1);
}

int    loadImages(t_engine *engine)
{
    if (!load_from_png("res/textures/wall_texture.png", &engine->cub_tex_left, *engine))
        return (0);
    if (!load_from_png("res/textures/wall_texture.png", &engine->cub_tex_right, *engine))
        return (0);
    if (!load_from_png("res/textures/wall_texture.png", &engine->cub_tex_top, *engine))
        return (0);
    if (!load_from_png("res/textures/wall_texture.png", &engine->cub_tex_bottom, *engine))
        return (0);
    return (1);
}
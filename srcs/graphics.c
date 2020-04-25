/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:26:17 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/25 13:50:41 by lrobino          ###   ########.fr       */
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

void        draw_ray_to_buffer(t_engine *eng, int x, int h, t_image tex, float offset, t_vec2d p_dir, float scale_f)
{
    int     y;
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
    dist = ft_map(h, 0, eng->buf.size.y, 0, 200);


    y = eng->buf.size.y / 2 - h / 2;
    while (h-- > 0 && x + (++y * (int)eng->buf.size.x) < eng->buf.size.x * eng->buf.size.y)
    {
        pos = (int)ft_map(offset, 0, 1, 0, tex.size.x) + (int)ft_map(i, -h_offset, start_h + h_offset, 0, tex.size.y) * tex.size.x;
#ifdef  HIGH_GRAPHICS
        t_color col;
        col = set_color(tex.data[pos]);
        col.channel.r = ft_constrain(ft_map(dist, 0, 50, 0, col.channel.r), 0, col.channel.r);
        col.channel.g = ft_constrain(ft_map(dist, 0, 50, 0, col.channel.g), 0, col.channel.g);
        col.channel.b = ft_constrain(ft_map(dist, 0, 50, 0, col.channel.b), 0, col.channel.b);
        if (pos < eng->buf.size.x * eng->buf.size.y)
        { 
            eng->buf.data[x + (y * (int)eng->buf.size.x)] = col.value;
        }
#else
        if (pos < tex.size.x * tex.size.y)
        { 
            eng->buf.data[x + (y * (int)eng->buf.size.x)] = tex.data[pos];
        }
#endif
        i++;
    }
    (void)p_dir;

    //FLOOR CASTING
    t_vec2d dir;
    t_vec2d cast;
    t_vec2d r_pos;
    t_vec2i t;
    float dirZ;
    float posZ = 0.5f;
    dir.y = sin(eng->player.rot + PI + (ft_map(x, 0, eng->buf.size.x, -radians(eng->player.fov) / 2, radians(eng->player.fov) / 2)));
    dir.x = cos(eng->player.rot + PI + (ft_map(x, 0, eng->buf.size.x, -radians(eng->player.fov) / 2, radians(eng->player.fov) / 2)));
    r_pos = eng->player.pos;

    while (y < eng->buf.size.y - 1)
    {
        //(void)scale_f;
        //dirZ = sin(PI + ft_map(y, 0, eng->buf.size.y, -radians(eng->player.fov / 2), radians(eng->player.fov) / 2)) * scale_f;
        dirZ = sin(PI + ft_map(y, 0, eng->buf.size.y, -0.5f, 0.5f)) * scale_f;
        cast = create_vector(dir.x * ((1.0F - posZ) / dirZ) + r_pos.x, dir.y * ((1.0F - posZ) / dirZ) + r_pos.y);
        t.x = (int)((cast.x - floor(cast.x)) * (tex.size.x));
        t.y = (int)((cast.y - floor(cast.y)) * (tex.size.y));

        //FIX OUT OF BOUNDS
#ifndef HIGH_GRAPHICS
        eng->buf.data[x + (y * (int)eng->buf.size.x)] = eng->cub_tex_floor.data[(int)(tex.size.x * t.x + t.y)];
        eng->buf.data[x + ((eng->buf.size.y - y++) * (int)eng->buf.size.x)] = eng->cub_tex_ceil.data[(int)(tex.size.x * t.x + t.y)];
#else
        dist = (scale_f * vec_mag(cast));//sin(PI + ft_map(y, 0, eng->buf.size.y, -0.5f, 0.5f)) * scale_f;
        t_color col;
        col = set_color(eng->buf.data[x + (y * (int)eng->buf.size.x)] = eng->cub_tex_floor.data[(int)(tex.size.x * t.x + t.y)]);
        col.channel.r = ft_constrain(ft_map(dist, MAX_VIEW, 0, 0, col.channel.r), 0, col.channel.r);
        col.channel.g = ft_constrain(ft_map(dist, MAX_VIEW, 0, 0, col.channel.g), 0, col.channel.g);
        col.channel.b = ft_constrain(ft_map(dist, MAX_VIEW, 0, 0, col.channel.b), 0, col.channel.b);
        if (pos < eng->buf.size.x * eng->buf.size.y)
        { 
            eng->buf.data[x + (y * (int)eng->buf.size.x)] = col.value;
        }
        col = set_color(eng->buf.data[x + ((eng->buf.size.y - y++) * (int)eng->buf.size.x)] = eng->cub_tex_ceil.data[(int)(tex.size.x * t.x + t.y)]);
        col.channel.r = ft_constrain(ft_map(dist, MAX_VIEW, 0, 0, col.channel.r), 0, col.channel.r);
        col.channel.g = ft_constrain(ft_map(dist, MAX_VIEW, 0, 0, col.channel.g), 0, col.channel.g);
        col.channel.b = ft_constrain(ft_map(dist, MAX_VIEW, 0, 0, col.channel.b), 0, col.channel.b);
        if (pos < eng->buf.size.x * eng->buf.size.y)
        { 
            eng->buf.data[x + (y * (int)eng->buf.size.x)] = col.value;
        }
#endif
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

int load_from_png(char *png, t_image *img, t_engine engine)
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
    if (!load_from_png("res/textures/dungeon_floor.png", &engine->cub_tex_floor, *engine))
        return (0);
    if (!load_from_png("res/textures/dungeon_ceil.png", &engine->cub_tex_ceil, *engine))
        return (0);
    return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:24:15 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/22 12:56:16 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

#include "engine.h"

typedef struct  s_color_channel
{
    int     b : 8;
    int     g : 8;
    int     r : 8;
}               t_color_channel;

typedef union   u_color
{
    t_color_channel channel;
    unsigned int value : 24;
}      

         t_color;

/*
**  IMAGE UTILS
*/
int    loadImages(t_engine *engine);


/*
**  COLOR UTILS
*/
t_color     create_color(unsigned char r, unsigned char g, unsigned char b);
t_color     create_gray(unsigned char luminosity);
t_color     set_color(int color_value);

/*
**  DRAW UTILS
*/
void        draw_line_to_buffer(t_image *buff, int x, int h, t_color color);
void        draw_ray_to_buffer(t_engine *eng, int x, int h, t_image tex, float offset);
void		draw_rect_to_buffer(t_image *buff, t_vec2f pos, t_vec2f size, t_color color);	

#endif
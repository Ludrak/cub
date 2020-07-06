/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:24:15 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/05 19:09:31 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

#include "engine.h"

# define TEX_NORTH  2
# define TEX_SOUTH  3
# define TEX_EAST   1
# define TEX_WEST   0

/*
**  IMAGE UTILS
*/
int         load_images(t_engine *engine);
int			load_from_xpm(char *xpm, t_image **img, t_engine *engine);

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
void        draw_ray_to_buffer(t_engine *eng, int x, t_cast cast);
void		draw_rect_to_buffer(t_image *buff, t_vec2f pos, t_vec2f size, t_color color);


#endif
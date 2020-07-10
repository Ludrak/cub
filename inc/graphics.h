/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:33:37 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/10 16:34:16 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "vectors.h"
# include "color.h"

# define TEX_NORTH  2
# define TEX_SOUTH  3
# define TEX_EAST   1
# define TEX_WEST   0

typedef struct	s_image
{
	void		*img_ptr;
	int			*data;

	int			sl;
	int			bpp;
	int			endian;
	t_vec2i		size;
}				t_image;

/*
**  COLOR UTILS
*/

t_color			create_color(unsigned char r, unsigned char g, unsigned char b);
t_color			create_gray(unsigned char luminosity);
t_color			set_color(int color_value);

/*
**  DRAW UTILS
*/

void			draw_line_to_buffer(t_image *buff, int x, int h, t_color color);
void			draw_rect_to_buffer
		(t_image *buff, t_vec2f pos, t_vec2f size, t_color color);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:24:15 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/11 11:47:06 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

#include "engine.h"

void		draw_line_to_buffer(t_image *buff, int x, int height);
void		draw_rect_to_buffer(t_image *buff, t_vec2d pos, t_vec2d size, int color);	

#endif
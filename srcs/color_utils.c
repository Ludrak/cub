/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 11:22:35 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 11:28:00 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_color    create_color(unsigned char r, unsigned char g, unsigned char b)
{
    t_color col;

    col.channel.r = r;
    col.channel.g = g;
    col.channel.b = b;
    return (col);
}

t_color    create_gray(unsigned char luminosity)
{
    t_color col;

    col.channel.r = luminosity;
    col.channel.g = luminosity;
    col.channel.b = luminosity;
    return (col);
}
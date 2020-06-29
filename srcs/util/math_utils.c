/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:06:35 by lrobino           #+#    #+#             */
/*   Updated: 2020/05/20 21:16:08 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

float   radians(float deg)
{
    return (deg * PI / 180);
}

float   degrees(float rad)
{
    return (rad * 180 / PI);
}

float   max(float a, float b)
{
    return (a > b ? a : b);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:06:35 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/19 13:12:42 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

float   radians (float deg)
{
    return (deg * PI / 180);
}

float   max(float a, float b)
{
    return (a > b ? a : b);
}
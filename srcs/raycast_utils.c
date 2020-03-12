/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:38:11 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 15:56:56 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_ray       create_ray (t_vec2d start, t_vec2d end)
{
    t_ray   ray;
    ray.start = start;
    ray.end = end;
    return (ray);
}

float ft_map(float value, float min1, float max1, float min2, float max2)
{
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}
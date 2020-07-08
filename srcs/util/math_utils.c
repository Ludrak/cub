/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:06:35 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/07 20:03:46 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

float	rad(float deg)
{
	return (deg * PI / 180);
}

float	deg(float rad)
{
	return (rad * 180 / PI);
}

float	max(float a, float b)
{
	return (a > b ? a : b);
}

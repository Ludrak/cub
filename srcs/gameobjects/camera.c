/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 22:08:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 14:21:26 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	init_camera(t_window win, t_camera *cam, float fov)
{
	cam->fov = fov > 180.0F ? 180 : fov;
	if (!(cam->z_buffer = malloc(sizeof(float) * win.size_x)))
		return ;
	// NOT WORKING KEEP 0.5F UNTIL FIX
	cam->height = 0.5F;
	cam->l_angle = 0;
	cam->r_angle = 0;
}

void	destroy_camera(t_camera *cam)
{
	free(cam->z_buffer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 22:08:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/03 14:14:26 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	init_camera(t_engine *eng, t_camera *cam, float fov)
{
	cam->fov = fov > 180.0F ? 180 : fov;
	if (!(cam->z_buffer = malloc(sizeof(float) * eng->win.size_x)))
		return ;
	// NOT WORKING KEEP 0.5F UNTIL FIX
	cam->height = 0.5F;
	cam->l_angle = 0;
	cam->r_angle = 0;
	eng->allocs |= CREATED_CAM;
}

void	destroy_camera(t_camera *cam)
{
	if (cam && cam->z_buffer)
		free(cam->z_buffer);
}

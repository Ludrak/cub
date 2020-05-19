/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 22:08:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/05/19 22:11:16 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void    init_camera(t_window win, t_camera *cam, int fov)
{
    if (!(cam = malloc(sizeof(t_camera))))
        return;
    cam->fov = fov;
    if (!(cam->z_buffer = malloc(sizeof(float) * win.size_x)))
        return;
    cam->l_angle = 0;
    cam->r_angle = 0;
}
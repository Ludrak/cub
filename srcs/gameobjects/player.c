/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:25:57 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 14:27:36 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_player	create_player(t_vec2d pos, float rot, float speed)
{
	t_player	player;

	player.pos = pos;
	player.plane = create_vector(0, 0);
	player.rot = rot;
	player.rotZ = 0;
	player.speed = speed;
	return (player);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:25:57 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 16:07:43 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_player	create_player(t_engine *eng, t_vec2d pos, float rot, float speed)
{
	eng->player.pos = pos;
	eng->player.plane = create_vector(0, 0);
	eng->player.rot = rot;
	eng->player.rotZ = 0;
	eng->player.speed = speed;
	return (eng->player);
}

void		move_player(t_player *player, int dir, t_map map)
{
	player->vel.x = (cos(player->rot) * player->speed * 0.01f) * dir;
	player->vel.y = (sin(player->rot) * player->speed * 0.01f) * dir;
	if (map.map[(int)(player->pos.x + 0.2F * ft_sign(player->vel.x))]
		[(int)(player->pos.y)]->id == CUB_AIR)
		player->pos.x += player->vel.x;
	if (map.map[(int)(player->pos.x)]
	[(int)(player->pos.y + 0.2F * ft_sign(player->vel.y))]->id == CUB_AIR)
		player->pos.y += player->vel.y;
}

void		rotate_player(t_player *player, int dir)
{
	player->rot += (float)dir * ROTATION_SPEED;
	if (player->rot < 0)
		player->rot = TWO_PI;
	else if (player->rot > TWO_PI)
		player->rot = 0;
}

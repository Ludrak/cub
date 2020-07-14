/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:25:57 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/11 14:15:33 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

t_player	create_player(t_engine *eng, t_vec2d pos, float rot, float speed)
{
	eng->player.pos = pos;
	eng->player.plane = vec2d(0, 0);
	eng->player.vel = vec2f(0, 0);
	eng->player.rot = rot;
	eng->player.speed = speed;
	eng->map.map[(int)pos.x][(int)pos.y] = get_cube_by_id(eng, CUB_AIR);
	if (eng->allocs & CREATED_PLAYER)
		p_exit(eng, "2 players on map", STATUS_MAP_FAILED);
	if (speed != 0)
		eng->allocs |= CREATED_PLAYER;
	return (eng->player);
}

void		move_player(t_player *player, int dir, float ld)
{
	player->vel.x = (cos(player->rot + (PI / 2) * ld) *
		player->speed * 0.01f) * dir;
	player->vel.y = (sin(player->rot + (PI / 2) * ld) *
		player->speed * 0.01f) * dir;
}

void		update_player(t_player *player, t_map map)
{
	if (fabs(player->vel.x) > 0.0001F)
	{
		if (map.map[(int)(player->pos.x + 0.25F * ft_sign(player->vel.x))]
			[(int)(player->pos.y)]->id == CUB_AIR)
			player->pos.x += (double)player->vel.x;
		player->vel.x /= __FRICTION;
	}
	else
		player->vel.x = 0;
	if (fabs(player->vel.y) > 0.0001F)
	{
		if (map.map[(int)(player->pos.x)]
		[(int)(player->pos.y + 0.25F * ft_sign(player->vel.y))]->id == CUB_AIR)
			player->pos.y += (double)player->vel.y;
		player->vel.y /= __FRICTION;
	}
	else
		player->vel.y = 0;
}

void		rotate_player(t_player *player, int dir)
{
	player->rot += (float)dir * ROTATION_SPEED;
	if (player->rot < 0)
		player->rot = TWO_PI;
	else if (player->rot > TWO_PI)
		player->rot = 0;
}

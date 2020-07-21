/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:25:16 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/20 12:48:17 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

void	handle_input(t_engine *eng)
{
	if (!eng->first_screen)
	{
		if (eng->keys.r_cam.pressed)
			rotate_player(&eng->player, 1);
		if (eng->keys.l_cam.pressed)
			rotate_player(&eng->player, -1);
		if (eng->keys.down.pressed)
			move_player(&eng->player, -1, 0);
		if (eng->keys.up.pressed)
			move_player(&eng->player, 1, 0);
		if (eng->keys.right.pressed)
			move_player(&eng->player, 1, -1);
		if (eng->keys.left.pressed)
			move_player(&eng->player, 1, 1);
		if (eng->keys.escape.pressed)
			p_exit(eng, "Escape key pressed", STATUS_SUCCESS);
	}
}

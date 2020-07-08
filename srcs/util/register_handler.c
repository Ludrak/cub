/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:32:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 17:01:32 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	register_builtins(t_engine *eng)
{
	int	i;

	i = 0;
	while (i < 4)
		eng->textures[i++] = NULL;
	eng->cubes = NULL;
	register_cube(
		eng, NULL, CUB_VOID);
	register_cube(
		eng, NULL, CUB_AIR);
}

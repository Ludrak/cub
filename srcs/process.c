/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:50:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/09 22:23:00 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "map_utils.h"
#include "process.h"

void    awake(void *param)
{
	t_engine    *engine;

	engine = param;
	engine->ptr = mlx_init();
}

void    setup(void *param)
{
	t_engine    *engine;
	t_window    window;
	t_map		*map;

	engine = param;

	window.size_x  = 1280; //TODO: PARSE
	window.size_y  = 720; //TODO: PARSE
	window.ptr     = mlx_new_window(engine->ptr, window.size_x, window.size_y, __PROJECT_NAME);
	engine->win    = &window;

	map = create_map(10, 100);
	print_map(*map);

	mlx_loop_hook(engine->ptr, runtime, &engine);

	mlx_loop(engine->ptr);
}

int    runtime (void *param)
{
	t_engine	*engine;

	engine = param;
	return (0);
}

void    p_exit (void *param)
{
	t_engine    *engine;
	
	engine = param;
}

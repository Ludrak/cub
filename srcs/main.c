/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:44:03 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 14:13:48 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

int		main(void)
{
	t_engine	*master;

	if (!(master = malloc(sizeof(t_engine))))
		return (0);
	awake(master);
	setup(master);
}

void	set_hooks(t_engine *eng)
{
	mlx_loop_hook(eng->ptr, runtime, eng);
	eng->keys = set_key_values();
	mlx_hook(eng->win.ptr, KeyPress, KeyPressMask, key_pressed_event, eng);
	mlx_hook(eng->win.ptr, KeyRelease, KeyReleaseMask, key_released_event, eng);
	mlx_hook(eng->win.ptr, DestroyNotify, StructureNotifyMask,
		on_window_destroyed, eng);
	mlx_loop(eng->ptr);
}

int		create_window(t_engine *eng, int size_x, int size_y, char *title)
{
	eng->win.size_x = size_x;
	eng->win.size_y = size_y;
	if (!(eng->win.ptr = mlx_new_window(eng->ptr, eng->win.size_x,
		eng->win.size_y, title)))
		p_exit(eng, "Unable to create window", STATUS_WIN_FAILED);
	eng->buf.size = create_vectori(eng->win.size_x, eng->win.size_y);
	return (1);
}

int		on_window_destroyed(void *engine)
{
	t_engine *eng;

	eng = (t_engine *)engine;
	p_exit(eng, "Window closed.", STATUS_WINDOW_CLOSED);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:44:03 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/05 19:38:51 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

int		main(void)
{
	t_engine	*master;

	if (!(master = malloc(sizeof(t_engine))))
		return (0);
	master->allocs = 0;
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
	int 	max_x;
	int 	max_y;

	if (!mlx_get_screen_size(eng->ptr, &max_x, &max_y))
		p_exit(eng, "Unable to get max screen size.", STATUS_WIN_FAILED);
	printf ("[MLX] : Creating window\n");
	eng->win.size_x = size_x > max_x ? max_x : size_x;
	eng->win.size_y = size_y > max_y ? max_y : size_y;
	if (!(eng->win.ptr = mlx_new_window(eng->ptr, eng->win.size_x,
		eng->win.size_y, title)))
		p_exit(eng, "Unable to create window.", STATUS_WIN_FAILED);
	eng->buf.size = create_vectori(eng->win.size_x, eng->win.size_y);
	eng->allocs |= CREATED_WIN;
	return (1);
}

int		on_window_destroyed(void *engine)
{
	t_engine *eng;

	eng = (t_engine *)engine;
	p_exit(eng, "Window closed.", STATUS_WINDOW_CLOSED);
	return (0);
}

void	print_exit_status(int status)
{
	if (status == STATUS_MAP_FAILED)
		printf ("[EXIT] Exit with status : MAP_FAILED\n");
	else if (status == STATUS_MAP_FAILED)
		printf ("[EXIT] Exit with status : REGISTER_FAILED\n");
	else if (status == STATUS_WIN_FAILED)
		printf ("[EXIT] Exited with status : WINDOW_FAILED\n");
	else if (status == STATUS_WINDOW_CLOSED)
		printf ("[EXIT] Exited with status : WINDOW_CLOSED\n");
	else if (status == STATUS_SUCCESS)
		printf ("[EXIT] Exit with status : SUCCESS\n");
}

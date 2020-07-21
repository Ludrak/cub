/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:44:03 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/21 00:10:58 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

int		main(int ac, char **av)
{
	t_engine	*master;

	if (!(master = malloc(sizeof(t_engine))))
		return (0);
	master->allocs = 0;
	master->first_screen = 0;
	if (ac > 1 && ac <= 3)
	{
		master->map_file = av[1];
		if (ac == 3 && !ft_strcmp(av[2], "--save"))
			master->first_screen = 1;
		else if (ac == 3)
			p_exit(master,
			"Unknown 2nd argument. \
Try with ./cub3D <map> --save.", STATUS_WIN_FAILED);
		awake(master);
		setup(master);
	}
	if (master->first_screen)
		p_exit(master, "Saved screenshot.", STATUS_SAVED_SCREEN);
	p_exit(master, "Wrong input parameters.", STATUS_INPUT_FAILED);
	return (0);
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
	int		max_x;
	int		max_y;

	if (!mlx_get_screen_size(eng->ptr, &max_x, &max_y))
		p_exit(eng, "Unable to get max screen size.", STATUS_WIN_FAILED);
	eng->win.size_x = size_x > max_x ? max_x : size_x;
	eng->win.size_y = size_y > max_y ? max_y : size_y;
	if (!eng->first_screen)
	{
		ft_printf("[MLX] : Creating window\n");
		if (!(eng->win.ptr = mlx_new_window(eng->ptr, eng->win.size_x,
			eng->win.size_y, title)))
			p_exit(eng, "Unable to create window.", STATUS_WIN_FAILED);
		eng->allocs |= CREATED_WIN;
	}
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

void	print_exit_status(int status)
{
	if (status == STATUS_MAP_FAILED)
		ft_printf("[EXIT] Exit with status : MAP_FAILED\n");
	else if (status == STATUS_MAP_FAILED)
		ft_printf("[EXIT] Exit with status : REGISTER_FAILED\n");
	else if (status == STATUS_WIN_FAILED)
		ft_printf("[EXIT] Exited with status : WINDOW_FAILED\n");
	else if (status == STATUS_WINDOW_CLOSED)
		ft_printf("[EXIT] Exited with status : WINDOW_CLOSED\n");
	else if (status == STATUS_SUCCESS)
		ft_printf("[EXIT] Exit with status : SUCCESS\n");
}

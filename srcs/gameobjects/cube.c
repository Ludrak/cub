/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 22:41:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 16:06:53 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		register_cube(t_engine *eng, char *tex_file, short id)
{
	t_cube	*cube;
	int		i;

	if (!(cube = malloc(sizeof(t_cube))))
		return (0);
	if (id != -1 && id != 0)
		if (!load_from_xpm(tex_file, &(cube->tex[0]), eng))
			p_exit(eng, "Cannot map texture file to cube", STATUS_IMG_FAILED);
	i = 1;
	while (i < 5)
		cube->tex[i++] = cube->tex[0];
	cube->id = id;
	if (!eng->cubes)
		eng->cubes = ft_lstnew(cube);
	else
		ft_lstadd_back(&eng->cubes, ft_lstnew(cube));
	printf("[REGISTER] : Registered cub id %d with texture : %s\n",
		id, tex_file);
	eng->allocs |= CREATED_CUBES;
	return (1);
}

int		register_cube_format(t_engine *eng, short id)
{
	t_cube	*cube;
	int		i;

	if (!(cube = malloc(sizeof(t_cube))))
		return (0);
	i = 0;
	while (i++ < 4)
	{
		if (!eng->textures[i - 1])
			p_exit(eng, "Unassigned all wall textures", STATUS_MAP_FAILED);
		cube->tex[i] = eng->textures[i - 1];
	}
	cube->id = id;
	if (!eng->cubes)
		eng->cubes = ft_lstnew(cube);
	else
		ft_lstadd_back(&eng->cubes, ft_lstnew(cube));
	printf("[REGISTER] Registered basic cub with id : %d\n", id);
	eng->allocs |= CREATED_CUBES;
	return (1);
}

t_cube	*get_cube_by_id(t_engine *eng, short id)
{
	t_cube	*c;
	t_list	*lst;

	lst = eng->cubes;
	while (lst)
	{
		c = (t_cube *)lst->content;
		if (c->id == id)
			return (c);
		lst = lst->next;
	}
	return (NULL);
}

void	unload_cube(t_list *cube)
{
	t_cube	*c;

	c = cube->content;
	printf("[UNLOADER] : Unloading cube with id : %d\n", c->id);
	free(c);
	free(cube);
}

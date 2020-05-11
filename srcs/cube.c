/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 22:41:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/05/11 10:42:07 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "engine.h"

int     register_cube(t_engine *eng, char *tex_file, short id)
{
    t_cube  *cube;

    if (!(cube = malloc(sizeof(t_cube))))
        return (0);
    if(id != -1 && id != 0) //We dont want a texture for void and air -> these will be native ids
        if (!load_from_xpm(tex_file, &cube->tex, *eng))
           p_exit(eng, "Cannot map texture file to cube", STATUS_IMG_FAILED);
    cube->id = id;
    if (!eng->cubes)
        eng->cubes = ft_lstnew(cube);
    else
        ft_lstadd_back(&eng->cubes, ft_lstnew(cube));
    return (1);
}

t_cube  *get_cube_by_id(t_engine *eng, short id)
{
    t_list  *lst;

    lst = eng->cubes;
    while (lst)
    {
        t_cube *c;
        c = (t_cube *) lst->content;
        if (c->id == id)
            return (c);
        lst = lst->next;
    }
    return (NULL);
}
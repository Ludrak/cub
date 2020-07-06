/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unloader_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:09:11 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/06 17:21:42 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void    unload_cubes(t_engine *eng)
{
    t_list  *tmp;
    
    while (eng->cubes)
    {
        tmp = eng->cubes->next;
        unload_cube(eng->cubes);
        eng->cubes = tmp;
    }
}

void    unload_sprites(t_engine *eng)
{
    t_list  *tmp;
    
    while (eng->loaded_sprites)
    {
        tmp = eng->loaded_sprites->next;
        unload_sprite(eng->loaded_sprites);
        eng->loaded_sprites = tmp;
    }
    while (eng->sprites)
    {
        tmp = eng->sprites->next;
        free(eng->sprites->content);
        free(eng->sprites);
        eng->sprites = tmp;
    }
}

void    unload_textures(t_engine *eng)
{
    t_list  *tmp;
    t_image *img;
    (void)img;
    while (eng->loaded_textures)
    {
        tmp = eng->loaded_textures->next;
        img = (t_image *)(eng->loaded_textures->content);
        mlx_destroy_image(eng->ptr, img->img_ptr);
        free(eng->loaded_textures->content);
        free(eng->loaded_textures);
        eng->loaded_textures = tmp;
    }
    mlx_destroy_image(eng->ptr, eng->buf.img_ptr);
}

void    unload_map(t_engine *eng)
{
    unsigned int    i = 0;
    
    while (i < eng->map.size_y)
    {
        free(eng->map.map[i]);
        i++;
    }
    free(eng->map.map);
}
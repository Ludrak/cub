/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:38:46 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 18:39:01 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int			load_from_xpm(char *png, t_image *img, t_engine engine)
{
	if (!png || !img)   
		return (0);
	(void)engine;//TODO
	if (!(img->img_ptr = mlx_xpm_file_to_image(engine.ptr, png, &img->size.x, &img->size.y)))
		return (0);
	if (!(img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian)))
		return (0);
	return (1);
}

int			loadImages(t_engine *engine)
{
	if (!load_from_xpm("res/textures/dungeon_floor.xpm", &engine->cub_tex_floor, *engine))
		return (0);
	if (!load_from_xpm("res/textures/dungeon_ceil.xpm", &engine->cub_tex_ceil, *engine))
		return (0);
	if (!load_from_xpm("res/textures/phantom.xpm", &engine->phantom, *engine))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:38:46 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/06 14:28:36 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int			load_from_xpm(char *xpm, t_image **img, t_engine *engine)
{
	printf ("[LOADIMAGE] : Loading image : %s\n", xpm);
	if (!xpm || !img)
		p_exit (engine, "Undefined path for texture.", STATUS_IMG_FAILED);
	if (!(*img = malloc(sizeof (t_image))))
		p_exit (engine, "Malloc break (try restarting).", STATUS_IMG_FAILED);
	ft_lstadd_back(&engine->loaded_textures, ft_lstnew(*img));
	if (!((*img)->img_ptr =
		mlx_xpm_file_to_image(engine->ptr, xpm, &(*img)->size.x, &(*img)->size.y)))
		p_exit (engine, "Cannot get image from path.", STATUS_IMG_FAILED);
	if (!((*img)->data = (int *)
		mlx_get_data_addr((*img)->img_ptr, &(*img)->bpp, &(*img)->sl, &(*img)->endian)))
		p_exit (engine, "Cannot get image data.", STATUS_IMG_FAILED);
	return (1);
}

int			load_images(t_engine *engine)
{
	engine->loaded_textures = NULL;
	if (!load_from_xpm(
		"res/textures/dungeon_floor.xpm", &engine->cub_tex_floor, engine))
		return (0);
	if (!load_from_xpm(
		"res/textures/dungeon_ceil.xpm", &engine->cub_tex_ceil, engine))
		return (0);
	return (1);
}

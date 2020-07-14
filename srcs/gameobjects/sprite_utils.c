/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:23:48 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/11 14:33:31 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

/*
**  REGISTER A SPRITE TO THE GAME THAT CAN BE LOADED LATER USING
**  add_sprite();
*/

int			register_sprite(t_engine *eng, char *tex_file, int sprite_id)
{
	t_sprite	*sprite;

	if (!(sprite = malloc(sizeof(t_sprite))))
		return (0);
	if (!load_from_xpm(tex_file, &sprite->sprite, eng))
		p_exit(eng, "Cannot map texture file to sprite", STATUS_IMG_FAILED);
	sprite->id = sprite_id;
	sprite->start_x = 0;
	sprite->end_x = 0;
	if (!eng->loaded_sprites)
		eng->loaded_sprites = ft_lstnew(sprite);
	else
		ft_lstadd_back(&eng->loaded_sprites, ft_lstnew(sprite));
	eng->allocs |= CREATED_SPRITE;
	ft_printf("[REGISTER] : Registered sprite id %d with texture : %s\n",
		sprite_id, tex_file);
	return (1);
}

t_sprite	*get_sprite_by_id(t_engine *eng, int id)
{
	t_list		*lst;
	t_sprite	*s;

	lst = eng->loaded_sprites;
	while (lst)
	{
		s = (t_sprite *)lst->content;
		if (s->id == id)
			return (s);
		lst = lst->next;
	}
	return (NULL);
}

int			add_sprite(t_engine *eng, int sprite_id, t_vec2d pos, float size)
{
	t_sprite	*sprite;
	t_sprite	*loaded;

	if (!(loaded = get_sprite_by_id(eng, sprite_id)))
		p_exit(eng, "Trying to add unregistered sprite to map.",
			STATUS_MAP_FAILED);
	if (!(sprite = malloc(sizeof(t_sprite))))
		p_exit(eng, "Malloc break. (try restarting)", STATUS_MAP_FAILED);
	sprite->id = loaded->id;
	sprite->sprite = loaded->sprite;
	sprite->size = size;
	sprite->pos = pos;
	sprite->height = 0.5F;
	eng->map.map[(int)pos.x][(int)pos.y] = get_cube_by_id(eng, CUB_AIR);
	if (!eng->sprites)
		eng->sprites = ft_lstnew(sprite);
	else
		ft_lstadd_back(&eng->sprites, ft_lstnew(sprite));
	return (1);
}

t_spt_info	create_spt_info(t_engine eng, t_sprite tmp)
{
	t_spt_info	info;

	info.spt_angle = atan2f(tmp.pos.y, tmp.pos.x);
	if (info.spt_angle < 0)
		info.spt_angle += (TWO_PI);
	if (eng.cam.r_angle > TWO_PI && info.spt_angle < PI)
		info.spt_angle += TWO_PI;
	if (eng.cam.l_angle < 0 && info.spt_angle > PI)
		info.spt_angle -= TWO_PI;
	info.spt_size = (tmp.size * eng.win.size_y) / tmp.dist;
	info.spt_height = (int)((1 - tmp.height - 0.5F) *
		(eng.win.size_y) / tmp.dist);
	return (info);
}

int			sprite_cmp(void *a, void *b)
{
	t_sprite	*sp_a;
	t_sprite	*sp_b;

	sp_a = (t_sprite *)a;
	sp_b = (t_sprite *)b;
	return (sp_a->dist < sp_b->dist);
}

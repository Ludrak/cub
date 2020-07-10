/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:02:44 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/10 16:43:02 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "libft.h"
# include "graphics.h"
# include "vectors.h"

typedef struct	s_spt_info
{
	float		spt_angle;
	float		spt_size;
	float		spt_height;
}				t_spt_info;

typedef struct	s_sprite
{
	t_image		*sprite;
	t_vec2d		pos;
	int			id;
	float		dist;
	float		size;
	float		height;
	float		start_x;
	float		end_x;
}				t_sprite;

int				sprite_cmp(void *a, void *b);
void			unload_sprite(t_list *sprite);

#endif

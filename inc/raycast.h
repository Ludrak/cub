/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:14:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/10 16:41:19 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "vectors.h"
# include "libft.h"
# include "cube.h"

/*
**  BLOCKS FACES
*/

# define NONE 0
# define LEFT 1
# define RIGHT 2
# define TOP 3
# define BOTTOM 4

typedef struct	s_ray
{
	t_vec2d start;
	t_vec2d end;
}				t_ray;

typedef __uint8_t	t_face;

typedef struct	s_cast
{
	float		wall_h;
	float		offset;
	float		scale_f;
	float		dist;
	t_vec2d		point;
	t_face		face;
	float		face_pos;
	t_cube		*cube;
	t_image		*tex;
}				t_cast;

/*
**	UTILS
*/
t_cast			create_cast_info
		(t_cube *cube, t_vec2d point, t_vec2d cast_block);
t_ray			create_ray (t_vec2d start, t_vec2d end);
float			ft_map(float value, t_vec2f range1, t_vec2f range2);

#endif

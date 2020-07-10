/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:32:42 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/10 16:32:48 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "graphics.h"

typedef struct	s_cube
{
	short		id;
	t_image		*tex[5];
}				t_cube;

#endif

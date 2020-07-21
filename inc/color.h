/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:09:51 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/20 13:13:18 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct	s_color_channel
{
	int		b : 8;
	int		g : 8;
	int		r : 8;
}				t_color_channel;

typedef union	u_color
{
	t_color_channel	channel;
	unsigned int	value : 28;
}				t_color;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:09 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 16:58:08 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_map	create_map(unsigned int size_x, unsigned int size_y, t_engine *eng)
{
	t_map			map;
	unsigned int	i;
	unsigned int	j;

	map.size_x = size_x;
	map.size_y = size_y;
	if (!(map.map = ft_calloc(size_y + 1, sizeof(t_cube **))))
		p_exit(eng, "Malloc break map (try restarting).", STATUS_MAP_FAILED);
	i = 0;
	while (i < size_y)
	{
		if (!(map.map[i] = ft_calloc(size_x + 1, sizeof(t_cube *))))
			p_exit(eng, "Malloc break (try restarting).", STATUS_MAP_FAILED);
		j = 0;
		while (j < size_x)
			map.map[i][j++] = get_cube_by_id(eng, CUB_VOID);
		i++;
	}
	eng->allocs |= CREATED_MAP;
	return (map);
}

void	draw_minimap(t_image *buffer, t_engine engine, t_vec2f pos)
{
	__uint32_t		i;
	__uint32_t		j;
	t_vec2f			c_pos;
	t_color			color;

	j = -1;
	while (++j < engine.map.size_x)
	{
		i = -1;
		while (++i < engine.map.size_y)
		{
			color.value = 0x202023;
			if (engine.map.map[i][j]->id == CUB_AIR)
				color.value = 0xe3e3e8;
			else if (engine.map.map[i][j]->id != CUB_VOID)
				color.value = 0x4c4c4c;
			c_pos.x = pos.x + i * (21);
			c_pos.y = pos.y + j * (21);
			draw_rect_to_buffer(buffer, c_pos, create_vectorf(20, 20), color);
		}
	}
	draw_rect_to_buffer(buffer,
	create_vectorf((int)(engine.player.pos.x * 20.0F - 5 + engine.player.pos.x),
	(int)(engine.player.pos.y * 20.0F - 5 + engine.player.pos.y)),
	create_vectorf(10, 10), create_color(255, 0, 0));
}

int		is_on_map(t_map map, float x, float y)
{
	if (x >= 0 && x < map.size_y && y >= 0 && y < map.size_x)
		return (1);
	return (0);
}

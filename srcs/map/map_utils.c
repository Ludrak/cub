/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:09 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/06 15:08:51 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_map       create_map(unsigned int size_x, unsigned int size_y, t_engine *eng)
{
	t_map			map;
	unsigned int	i;
	unsigned int	j;
	
	map.size_x = size_x;
	map.size_y = size_y;
	if (!(map.map = ft_calloc(size_y + 1, sizeof(t_cube **))))
		p_exit (eng, "Malloc break map (try restarting).", STATUS_MAP_FAILED);
	i = 0;
	while (i < size_y)
	{
		if (!(map.map[i] = ft_calloc(size_x + 1, sizeof(t_cube *))))
			p_exit (eng, "Malloc break map (try restarting).", STATUS_MAP_FAILED);
		j = 0;
		while (j < size_x)
			map.map[i][j++] = get_cube_by_id(eng, CUB_VOID);
		i++;
	}
	eng->allocs |= CREATED_MAP;
	return (map);
}

void        print_map(t_map map)
{
	__uint32_t  i;
	__uint32_t  j;

	write (1, "[MAP - CUB3D]\n", 14);
	j = 0;
	while (j < map.size_x)
	{
		i = 0;
		while (i < map.size_y)
		{
			/*if (map.map[i][j]->id == CUB_VOID)
				write (1, " ", 1);
			if (map.map[i][j]->id == CUB_AIR)
				write (1, "_", 1);
				//write (1, "\u254B\u254B", 6);
			else
				write (1, "X", 1);
				//write (1, "\u2588\u2588", 6);*/
			if (map.map[i][j]->id == CUB_AIR)
				write (1, " ", 1);
			else
				write (1, ft_itoa(map.map[i][j]->id), 1);
		   i++;
		}
		j++;
		write (1, "\n", 1);
	}
}

void        draw_minimap(t_image *buffer, t_engine engine, t_vec2f pos)
{
	__uint32_t      i;
	__uint32_t      j;
	t_vec2f         c_pos;
	t_color         color;

	j = 0;
	draw_rect_to_buffer(buffer, 
						create_vectorf(pos.x - 2, pos.y - 2), 
						create_vectorf(engine.map.size_y * (MINIMAP_CUB_SIZ + 1) + 4,
						engine.map.size_x * (MINIMAP_CUB_SIZ + 1) + 4),
						create_gray(31));
	while (j < engine.map.size_x)
	{
		i = 0;
		while (i < engine.map.size_y)
		{
			if (engine.map.map[i][j]->id == CUB_AIR)
				color.value = 0xe3e3e8;
			else if (engine.map.map[i][j]->id != CUB_VOID)
				color.value = 0x4c4c4c;
			else
				color.value = 0x202023;
			
			c_pos.x = pos.x + i * (MINIMAP_CUB_SIZ + 1);
			c_pos.y = pos.y + j * (MINIMAP_CUB_SIZ + 1);
			draw_rect_to_buffer(buffer, c_pos, create_vectorf(MINIMAP_CUB_SIZ, MINIMAP_CUB_SIZ), color);
			i++;
		}
		j++;
	}
	draw_rect_to_buffer(buffer, create_vectorf((int)(engine.player.pos.x * (float)MINIMAP_CUB_SIZ) - 5 + (int) engine.player.pos.x,
										(int)(engine.player.pos.y * (float)MINIMAP_CUB_SIZ) - 5 + (int) engine.player.pos.y),
							create_vectorf(10, 10), create_color(255, 0, 0));
}

int		is_on_map(t_map map, float x, float y)
{
	if (x >= 0 && x < map.size_y && y >= 0 && y < map.size_x)
		return (1);
	return (0);
}
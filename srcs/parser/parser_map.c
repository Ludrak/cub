/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:21:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/19 00:44:35 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

t_vec2i		get_map_size(t_list *lines)
{
	int		x;
	int		y;
	int		ltmp;

	x = 0;
	y = 0;
	while (lines)
	{
		if (x < (ltmp = ft_strlen((char *)lines->content)))
			x = ltmp;
		lines = lines->next;
		y++;
	}
	return (create_vectori(x, y));
}

float		parse_dir(char dir_char)
{
	if (dir_char == 'N')
		return (PI + PI / 2);
	else if (dir_char == 'S')
		return (PI / 2);
	else if (dir_char == 'W')
		return (PI);
	return (0);
}

void		parse_xline(t_engine *eng, int y, char *line)
{
	int		x;

	x = 0;
	while (line && *line)
	{
		if ((ft_isdigit(*line) || *line == ' ') && x < (int)eng->map.size_y)
		{
			if (*line == '2' && eng->format == FORMAT)
				add_sprite(eng, 0, vec2d(x + 0.5F, y + 0.5F), 0.75F);
			else if (!(eng->map.map[x][y] =
				get_cube_by_id(eng, (*line == ' ') ? CUB_VOID : (*line - '0'))))
				p_exit(eng, "Invalid cub id on map.", STATUS_MAP_FAILED);
		}
		else if ((*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W'))
			create_player(eng, vec2d(x + 0.5F, y + 0.5F),
			parse_dir(*line), PLAYER_SPEED);
		else if (eng->format == CUSTOM_F && get_sprite_by_id(eng, *line - 'A'))
			add_sprite(eng, *line - 'A', vec2d(x + 0.5F, y + 0.5F), 1.0F);
		else
			p_exit(eng, "Unparsable id on map. aborting.", STATUS_MAP_FAILED);
		x++;
		line++;
	}
}

int			parse_map(t_engine *eng, t_list *lines)
{
	t_list	*first;
	t_vec2i	size;
	int		y;

	y = 0;
	first = lines;
	while (lines)
		if (ft_strlen(lines->content) == 0 ||
			(!ft_isdigit(*(char *)(lines->content)) &&
			*(char *)(lines->content) != ' '))
			lines = lines->next;
		else
			break ;
	size = get_map_size(lines);
	eng->map = create_map(size.y, size.x, eng);
	eng->player = create_player(eng, vec2d(0, 0), 0, 0);
	while (lines)
	{
		parse_xline(eng, y++, (char *)lines->content);
		lines = lines->next;
	}
	if (eng->player.pos.x == 0 && eng->player.pos.y == 0)
		p_exit(eng, "No player on map. aborting.", STATUS_MAP_FAILED);
	ft_lstclear(&first, free);
	return (1);
}

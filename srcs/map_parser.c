/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:23:20 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 11:41:10 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include <stdio.h>

static t_map_parse_buffer  *parse_map_to_buffer(int fd)
{
    char                *line;
    t_map_parse_buffer  *buffer;
    t_map_parse_buffer  *first;
    
    if (!(buffer = malloc(sizeof(t_map_parse_buffer))))
        return (NULL);
    first = buffer;
    while (get_next_line(fd, &line) > 0)
    {
        buffer->line = line;
        if (!(buffer->next = malloc(sizeof(t_map_parse_buffer))))
            return (NULL);
        buffer = buffer->next;
    }
    buffer->line = line;
    buffer->next = NULL;
    return (first);
}

static void                 free_map_buffer(t_map_parse_buffer *buffer)
{
    t_map_parse_buffer  *tmp;
    
    while (buffer->next)
    {
        free (buffer->line);
        tmp = buffer;
        buffer = buffer->next;
        free(tmp); 
    }
}

t_map                       *parse_map(int fd)
{
    t_map               *map;
    t_map_parse_buffer  *buffer;
    t_map_parse_buffer  *first;
    t_vec2d             map_size;

    int                 i;
    int                 j;
   
    buffer = parse_map_to_buffer(fd);
    first = buffer;
    map_size.y = 0;
    while (buffer)
    {
        map_size.x = (ft_strlen(buffer->line) > map_size.x) ? ft_strlen(buffer->line) : map_size.x;
        map_size.y++;
        buffer = buffer->next;   
    }
    map = create_map(map_size.y, map_size.x);
    buffer = first;
    
    j = 0;
    while (buffer)
    {
        i = 0;
        while (buffer->line[i])
        {
            if (buffer->line[i] == ' ')
                map->map[i][j]  = CUB_VOID;
            else if (buffer->line[i] == '0')
                map->map[i][j]  = CUB_AIR;
            else if (buffer->line[i] == '1')
                map->map[i][j]  = CUB_BLOCK;
            else
                //TODO CHECK
                map->map[i][j]  = CUB_VOID;
            i++;
        }
        buffer = buffer->next;
        j++;
    }
    free_map_buffer(first);
    print_map(*map);
    return (map);
}

int                         check_map(t_map map)
{
    __uint32_t  x;
    __uint32_t  y;

    int         last;
    int         current;

    last = 0;
    x = 0;
    while (x < map.size_x)
    {
        y = 0;
        while (y < map.size_y)
        {
            current = last;
            last = map.map[y][x];
            if (current + last == 1)
                return (0);
            y++;
        }
        x++;
    }
    last = 0;
    y = 0;
    while (y < map.size_y)
    {
        x = 0;
        while (x < map.size_x)
        {
            current = last;
            last = map.map[y][x];
            if (current + last == 1)
                return (0);
            x++;
        }
        y++;
    }
    return (1);
}

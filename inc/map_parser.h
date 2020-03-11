/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:21:38 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/11 18:48:05 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

#include "get_next_line.h"
#include "engine.h"

typedef struct  s_map_parse_buffer
{
    char                        *line;
    struct s_map_parse_buffer   *next;
}               t_map_parse_buffer;

t_map   *parse_map(int fd);
int     check_map(t_map map);

#endif
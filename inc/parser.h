/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:32:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/05 17:56:30 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "engine.h"

# define FORMAT     1
# define CUSTOM_F   2

/*
**  REGISTRY CHECKERS
*/
int     check_resolution(char **argv);
int     check_path(char **argv);
int     check_color(char **argv);
int		check_id_register(char **argv);


void    parse_registry(t_engine *eng, char *file);
int     parse_map(t_engine *eng, t_list *lines);

#endif
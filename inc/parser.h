/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:32:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/18 17:29:05 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

# define FORMAT     1
# define CUSTOM_F   2

/*
**  REGISTRY CHECKERS
*/
int		check_resolution(char **argv);
int		check_path(char **argv);
int		check_color(char **argv);
int		check_id_register(char **argv);
int		check_spt_register(char **argv);

#endif

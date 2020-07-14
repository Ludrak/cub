/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:51:19 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/11 14:29:00 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "engine.h"
# include "ft_printf.h"

# define STATUS_INPUT_FAILED	-5
# define STATUS_REGISTER_FAILED -4
# define STATUS_WIN_FAILED      -3
# define STATUS_IMG_FAILED      -2
# define STATUS_MAP_FAILED      -1
# define STATUS_SUCCESS         0
# define STATUS_WINDOW_CLOSED   1

void	awake(t_engine *eng);
void	setup(t_engine *eng);
int		runtime(t_engine *eng);
void	p_exit(t_engine *eng, char *exit_log, int exit_status);

#endif

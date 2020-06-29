/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:51:19 by lrobino           #+#    #+#             */
/*   Updated: 2020/06/29 13:03:51 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

//OVERRIDE THIS IN PROCESS.C
#include "engine.h"

//EXIT STATUS
# define STATUS_WIN_FAILED      -3
# define STATUS_IMG_FAILED      -2
# define STATUS_MAP_FAILED      -1
# define STATUS_SUCCESS         0
# define STATUS_WINDOW_CLOSED   1

//  First execution
void    awake(t_engine *);

//  Executed right before awake
void    setup(t_engine *);

//  Executed at each frame
int    runtime(t_engine *);

//  Executed on exit
void    p_exit(t_engine *, char *exit_log, int exit_status);

#endif
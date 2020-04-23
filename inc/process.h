/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:51:19 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/22 14:27:01 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

//OVERRIDE THIS IN PROCESS.C
#include "engine.h"

//EXIT STATUS
# define STATUS_IMG_FAILED  -2
# define STATUS_MAP_FAILED  -1
# define STATUS_SUCCESS     0

//  First execution
void    awake(t_engine *);

//  Executed right before awake
void    setup(t_engine *);

//  Executed at each frame
int    runtime(t_engine *);

//  Executed on exit
void    p_exit(t_engine *, char *exit_log, int exit_status);

#endif
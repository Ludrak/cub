/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:51:19 by lrobino           #+#    #+#             */
/*   Updated: 2020/04/21 11:27:56 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

//OVERRIDE THIS IN PROCESS.C
#include "engine.h"

//  First execution
void    awake(t_engine *);

//  Executed right before awake
void    setup(t_engine *);

//  Executed at each frame
int    runtime(t_engine *);

//  Executed on exit
void    p_exit(t_engine *, char *exit_log);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:51:19 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/11 11:32:38 by lrobino          ###   ########lyon.fr   */
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
void    p_exit(t_engine *);

#endif
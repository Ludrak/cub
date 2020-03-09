/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:51:19 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/09 17:17:35 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

//OVERRIDE THIS IN PROCESS.C

//  First execution
void    awake(void *);

//  Executed right before awake
void    setup(void *);

//  Executed at each frame
int    runtime(void *);

//  Executed on exit
void    p_exit(void *);

#endif
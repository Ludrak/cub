/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:44:03 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/11 11:35:37 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

int main()
{
    t_engine    *master;

	if (!(master = malloc (sizeof(t_engine))))
		return (0);
    awake(master);
    setup(master);
}
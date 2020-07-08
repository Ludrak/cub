/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:19:20 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 17:08:42 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		check_id_register(char **argv)
{
	int	ac;

	ac = 0;
	while (argv[++ac] != NULL)
		;
	if (ac == 3)
	{
		if (!ft_strnum(argv[2]))
			return (0);
	}
	else
		return (0);
	return (1);
}

int		check_resolution(char **argv)
{
	int	ac;

	ac = 0;
	while (argv[++ac] != NULL)
		;
	if (ac == 3)
	{
		if (!ft_strnum(argv[1]) || !ft_strnum(argv[2]))
			return (0);
	}
	else
		return (0);
	return (1);
}

int		check_path(char **argv)
{
	int	ac;

	ac = 0;
	while (argv[++ac] != NULL)
		;
	if (ac == 2)
		return (1);
	return (0);
}

int		check_color(char **argv)
{
	int	ac;

	ac = 0;
	while (argv[++ac] != NULL)
		;
	if (ac == 4)
	{
		ac = 0;
		while (ac < 3)
			if (!ft_strnum(argv[ac++ + 1]))
				return (0);
		return (1);
	}
	return (0);
}

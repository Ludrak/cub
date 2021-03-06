/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:19:20 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/23 07:41:41 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		check_spt_register(char **argv)
{
	int	ac;

	ac = 0;
	while (argv[++ac] != NULL)
		;
	if (ac == 3)
		return (1);
	return (0);
}

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
	int			ac;
	static int	is_win = 0;

	ac = 0;
	while (argv[++ac] != NULL)
		;
	if (ac == 3)
	{
		if (!ft_strnum(argv[1]) || !ft_strnum(argv[2]))
			return (0);
		if (is_win)
			return (0);
		is_win = 1;
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
	int			ac;
	int			col_tmp;
	static int	checked = 0;

	ac = 0;
	while (argv[++ac] != NULL)
		;
	if (ac == 4)
	{
		checked++;
		ac = 0;
		while (ac < 3)
		{
			if (ft_strnum(argv[ac++ + 1]) && checked <= 2)
			{
				if ((col_tmp = ft_atoi(argv[ac])) > 255
					|| col_tmp < 0)
					return (0);
			}
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

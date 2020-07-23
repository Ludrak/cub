/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 06:54:22 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/23 07:40:17 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

char		**split_line(t_engine *eng, char *line)
{
	char	**av;
	int		comma;
	int		i;
	int		j;

	i = 0;
	av = ft_splitcharset(line, " \t\v\f\r");
	while (av[i])
	{
		j = 0;
		comma = 0;
		while (av[i][j])
		{
			if (av[i][j++] == ',')
			{
				if (!comma)
					comma = 1;
				else
					p_exit(eng, "Extraneous comma", STATUS_MAP_FAILED);
			}
		}
		i++;
	}
	ft_freestab(av);
	return (ft_splitcharset(line, ", \t\v\f\r"));
}

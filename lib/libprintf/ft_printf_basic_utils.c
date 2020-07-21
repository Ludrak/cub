/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_basic_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:06:46 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:18:34 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_null(t_pf_data *data)
{
	data->content = ft_strdup("(null)");
	data->type = PF_NULL;
	data->len = 6;
	return (1);
}

t_bool		pf_numeric_type(t_type type)
{
	if (type == PF_INT || type == PF_UINT || type == PF_DEC ||
	type == PF_LOW_HEX || type == PF_CAP_HEX)
		return (TRUE);
	return (FALSE);
}

t_bool		pf_is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'p'
	|| c == 'i' || c == 'u' || c == 'x' || c == 'X'
	|| c == '%' || c == 'o')
		return (TRUE);
	return (FALSE);
}

t_bool		pf_is_flag(char c)
{
	if (c == '0' || c == ' ' || c == '-' || c == '#'
	|| c == '+')
		return (TRUE);
	return (FALSE);
}

char		*pf_fjoin(char *a, char *b, int mode)
{
	char	*output;

	output = ft_strjoin(a, b);
	if (mode == PF_FREE_MODE_FIRST || mode == PF_FREE_MODE_BOTH)
		free(a);
	if (mode == PF_FREE_MODE_LAST || mode == PF_FREE_MODE_BOTH)
		free(b);
	return (output);
}

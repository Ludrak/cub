/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:46:43 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:18:37 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_parse_char(t_pf_data *data, va_list args)
{
	if (data->type == PF_CHAR)
	{
		data->content = ft_calloc(2, sizeof(char));
		if (!(data->content[0] = (char)va_arg(args, int)))
			data->content[0] = '\0';
		data->len = 1;
		return (1);
	}
	return (0);
}

int		pf_parse_string(t_pf_data *data, va_list args)
{
	char	*buf;

	if (data->type == PF_STRING)
	{
		if (data->precision != 0)
		{
			if (!(buf = va_arg(args, char *)))
				return (pf_null(data));
		}
		else
		{
			va_arg(args, void *);
			buf = "";
		}
		data->content = ft_strdup(buf);
		data->len = ft_strlen(buf);
		return (1);
	}
	return (0);
}

int		pf_parse_numeric(t_pf_data *data, va_list args)
{
	char	*n_buf;

	if (data->type == PF_INT || data->type == PF_DEC)
	{
		if (!(n_buf = ft_itoa(va_arg(args, int))))
			return (pf_null(data));
		data->content = ft_strdup(n_buf);
		data->len = ft_strlen(n_buf);
		free(n_buf);
		return (1);
	}
	else if (data->type == PF_UINT)
	{
		if (!(n_buf = ft_utoa((unsigned int)va_arg(args, int))))
			return (pf_null(data));
		data->content = ft_strdup(n_buf);
		data->len = ft_strlen(n_buf);
		free(n_buf);
		return (1);
	}
	return (0);
}

int		pf_parse_pointer(t_pf_data *data, va_list list)
{
	intptr_t	val;

	if (data->type == PF_POINTER)
	{
		if (!(val = (intptr_t)va_arg(list, void *)))
		{
			if (data->precision == 0)
			{
				va_arg(list, void *);
				data->content = ft_strdup("");
				data->len = 0;
				return (1);
			}
			data->content = ft_strdup("0");
			data->len = 1;
			return (1);
		}
		else
		{
			data->content = ft_ltoa_base((intptr_t)val, "0123456789abcdef");
			data->len = ft_strlen(data->content);
		}
		return (1);
	}
	return (0);
}

int		pf_parse_hexadecimal(t_pf_data *data, va_list list)
{
	int		val;
	char	*base;

	if (data->type == PF_LOW_HEX || data->type == PF_CAP_HEX)
	{
		base = (data->type == PF_LOW_HEX) ?
			"0123456789abcdef" : "0123456789ABCDEF";
		val = va_arg(list, int);
		data->content = ft_itoa_base(val, base);
		data->len = ft_strlen(data->content);
		return (1);
	}
	return (0);
}

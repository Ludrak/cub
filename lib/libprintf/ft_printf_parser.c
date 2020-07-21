/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:06:42 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:18:35 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_parse_flags(char *format, t_flags *flags)
{
	int		len;

	len = 0;
	*flags = 0;
	while (pf_is_flag(*format))
	{
		if (*format == '0' && !(*flags & PF_MINUS))
			*flags |= PF_ZERO;
		if (*format == '-' && !((*flags &= ~PF_ZERO) & PF_ZERO))
			*flags |= PF_MINUS;
		if (*format == '+' && !((*flags &= ~PF_SPACE) & PF_SPACE))
			*flags |= PF_PLUS;
		if (*format == ' ' && !(*flags & PF_PLUS))
			*flags |= PF_SPACE;
		if (*format == '#')
			*flags |= PF_HASH;
		len++;
		format++;
	}
	return (len);
}

void		pf_parse_content(char *format, t_pf_data *data, va_list args)
{
	int		(*pf_parse[5])(t_pf_data *data, va_list args);
	int		i;

	i = 0;
	pf_parse[0] = pf_parse_char;
	pf_parse[1] = pf_parse_string;
	pf_parse[2] = pf_parse_numeric;
	pf_parse[3] = pf_parse_pointer;
	pf_parse[4] = pf_parse_hexadecimal;
	pf_get_format_type(format, data);
	if (data->type == PF_PRC)
	{
		data->content = ft_strdup("%");
		data->len = 1;
		return ;
	}
	while (!(*pf_parse[i])(data, args))
	{
		i++;
	}
}

void		pf_parse_padding(char *format, t_pf_data *data, va_list args)
{
	int		val;

	val = pf_get_number(format, args);
	if (val < 0)
	{
		data->flags |= PF_MINUS;
		data->flags &= ~PF_ZERO;
	}
	data->padding = (val < 0) ? -val : val;
	if (ft_isdigit(*format) || *format == '-' || *format == '*')
		data->flags |= PF_PADD;
}

void		pf_parse_precision(char *format, t_pf_data *data, va_list args)
{
	int		val;

	while (*format && *format != '.' && !pf_is_type(*format))
		format++;
	if (*format++ == '.')
	{
		val = pf_get_number(format, args);
		if (val >= 0)
		{
			data->precision = val;
			data->flags |= PF_PREC;
		}
		else
			data->precision = -1;
		return ;
	}
	data->precision = -1;
}

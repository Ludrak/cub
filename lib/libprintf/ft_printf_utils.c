/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:06:37 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:18:36 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		pf_get_format_type(char *f, t_pf_data *data)
{
	int len;

	len = 1;
	while (!pf_is_type(*f))
	{
		len++;
		if (!++f)
			return (0);
	}
	if (data)
		data->type = (t_type)(*f);
	return (len);
}

int			pf_get_number(char *flags, va_list args)
{
	int		val;

	if (*flags == '*')
	{
		val = va_arg(args, int);
	}
	else
	{
		if (*flags != '-' && !ft_isdigit(*flags))
			return (0);
		val = ft_atoi(flags);
	}
	return (val);
}

void		pf_set_padding(t_pf_data *data)
{
	char	padding_char;
	int		prefix;
	int		content_len;

	content_len = data->len;
	padding_char = ((!(data->flags & PF_PREC) || data->type == PF_PRC) &&
		(data->flags & PF_ZERO) ? '0' : ' ');
	if (data->content[0] == '\0' && data->type == PF_CHAR &&
		data->flags & PF_MINUS)
		content_len = 0;
	prefix = (padding_char == '0') ? pf_get_prefix(data, &content_len) : 0;
	if (data->padding > content_len)
	{
		pf_apply_padding(data, content_len, padding_char, prefix);
	}
}

void		pf_set_precision(t_pf_data *data)
{
	int		prefix;
	char	*content_buf;

	if (data->precision < 0)
		return ;
	content_buf = data->content;
	prefix = 0;
	if (pf_numeric_type(data->type))
		prefix = pf_get_prefix(data, NULL);
	if (pf_numeric_type(data->type) || data->type == PF_POINTER)
	{
		pf_apply_precision(data, prefix);
	}
	else if (data->type != PF_PRC)
	{
		if (data->precision < (int)ft_strlen(content_buf))
		{
			content_buf = data->content;
			data->len -= ft_strlen(content_buf) - data->precision;
			ft_bzero(content_buf + data->precision,
				ft_strlen(content_buf) - data->precision);
		}
	}
}

void		pf_set_flags(t_pf_data *data)
{
	t_flags flags;
	t_type	type;

	flags = data->flags;
	type = data->type;
	if (pf_numeric_type(data->type) &&
		data->type != PF_LOW_HEX && data->type != PF_CAP_HEX)
		if (ft_isdigit(data->content[0]) && data->type != PF_UINT)
		{
			if (data->flags & PF_PLUS)
				data->content = pf_fjoin("+", data->content, PF_FREE_MODE_LAST);
			else if (data->flags & PF_SPACE)
				data->content = pf_fjoin(" ", data->content, PF_FREE_MODE_LAST);
			data->len = (data->flags & (PF_PLUS | PF_SPACE))
				? data->len + 1 : data->len;
		}
	pf_apply_flag_hex(data, flags, type);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_basic_utils_bis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:06:50 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:18:34 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_get_prefix(t_pf_data *data, int *content_len)
{
	int		prefix;

	prefix = 0;
	if (data->flags & PF_PLUS || data->flags & PF_SPACE ||
		(pf_numeric_type(data->type) && (data->content[0] == '-')))
		prefix = 1;
	if (data->flags & PF_HASH || ((data->type & PF_LOW_HEX ||
	data->type & PF_CAP_HEX) && (!(data->flags & PF_ZERO) &&
											data->flags & PF_HASH)))
	{
		prefix = 2;
		if (content_len)
			content_len -= 2;
	}
	return (prefix);
}

void	pf_apply_padding(t_pf_data *data, int content_len,
										char padding_char, int prefix)
{
	char	*buf;
	char	*content_buf;

	content_buf = data->content;
	if (!(buf = ft_calloc(data->padding - content_len + 1, sizeof(char))))
		return ;
	ft_memset(buf, padding_char, data->padding - (content_len));
	data->len += ft_strlen(buf);
	if (!(data->flags & PF_MINUS))
		data->content = ft_strinsert(content_buf, buf, prefix);
	else
	{
		data->content = ft_strinsert(buf, content_buf, prefix);
		if (content_len == 0 && data->type == PF_CHAR &&
				!(data->content[0] = '\0'))
			data->len = ft_strlen(buf);
	}
	free(buf);
	free(content_buf);
}

void	pf_apply_precision(t_pf_data *data, int prefix)
{
	char	*content_buf;
	char	*n_buf;

	content_buf = data->content;
	if (data->precision > data->len - prefix)
	{
		if (!(n_buf = ft_calloc(data->precision - (data->len - prefix) + 1,
												sizeof(char))))
			return ;
		ft_memset(n_buf, '0', data->precision - (data->len - prefix));
		data->len += ft_strlen(n_buf);
		data->content = ft_strinsert(data->content, n_buf, prefix);
		free(n_buf);
		free(content_buf);
	}
	if (data->precision == 0 && data->content[prefix] == '0' &&
		pf_numeric_type(data->type))
	{
		ft_bzero(data->content + prefix, data->len - prefix);
		data->len = prefix;
	}
}

void	pf_apply_flag_hex(t_pf_data *data, t_flags flags, t_type type)
{
	if (!data->content || data->content[0] == '0')
		data->flags &= ~PF_HASH;
	if (data->type == PF_PRC)
		return ;
	if ((flags & PF_HASH || type == PF_LOW_HEX || type == PF_POINTER) &&
	!(type == PF_CAP_HEX))
		if ((flags & PF_HASH && data->content[0] != '0') || type == PF_POINTER)
		{
			data->content = pf_fjoin("0x", data->content, PF_FREE_MODE_LAST);
			data->len += 2;
		}
	if (type == PF_CAP_HEX && flags & PF_HASH && data->content[0] != '0')
	{
		data->len += 2;
		data->content = pf_fjoin("0X", data->content, PF_FREE_MODE_LAST);
	}
}

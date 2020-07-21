/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:06:56 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 16:18:57 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define PF_CHAR	'c'
# define PF_STRING	's'
# define PF_DEC		'd'
# define PF_INT		'i'
# define PF_UINT	'u'
# define PF_POINTER	'p'
# define PF_LOW_HEX	'x'
# define PF_CAP_HEX 'X'
# define PF_PRC		'%'
# define PF_NULL	0

# define PF_MINUS	1
# define PF_PLUS	2
# define PF_ZERO	4
# define PF_HASH	8
# define PF_SPACE	16
# define PF_PREC	32
# define PF_PADD	64

# define TRUE		1
# define FALSE		0

# define PF_FREE_MODE_FIRST		0
# define PF_FREE_MODE_LAST		1
# define PF_FREE_MODE_BOTH		2
# define PF_FREE_MODE_NONE		3

typedef char	t_bool;
typedef char	t_type;
typedef char	t_flags;

typedef struct		s_pf_data
{
	t_type	type;
	char	*content;
	char	*prefix;
	t_flags	flags;
	int		len;
	int		f_len;
	int		padding;
	int		precision;
}					t_pf_data;

/*
**		FT_PRINTF TYPES PARSER
*/
int					pf_parse_char(t_pf_data *data, va_list args);
int					pf_parse_string(t_pf_data *data, va_list args);
int					pf_parse_numeric(t_pf_data *data, va_list args);
int					pf_parse_pointer(t_pf_data *data, va_list args);
int					pf_parse_hexadecimal(t_pf_data *data, va_list list);

/*
**		FT_PRINTF FLAGS PARSER
*/
void				pf_parse_content(char *flags,
								t_pf_data *data, va_list args);
void				pf_parse_precision(char *flags,
								t_pf_data *data, va_list args);
void				pf_parse_padding(char *flags,
								t_pf_data *data, va_list args);
int					pf_parse_flags(char *format,
								t_flags *flags);

/*
**		FT_PRINTF_UTILS
*/
size_t				pf_get_format_type(char *flags, t_pf_data *data);
void				pf_set_padding(t_pf_data *data);
void				pf_set_precision(t_pf_data *data);
void				pf_set_flags(t_pf_data *data);
int					pf_get_number(char *flags, va_list args);

/*
**		FT_PRINTF BASIC UTILS
*/
t_bool				pf_is_type(char c);
t_bool				pf_is_flag(char c);
t_bool				pf_numeric_type(t_type type);
int					pf_null(t_pf_data *data);
char				*pf_fjoin(char *a, char *b, int mode);

/*
**		FT_PRINTF BASIC UTILS BIS
*/
int					pf_get_prefix(t_pf_data *data, int *content_len);
void				pf_apply_padding(t_pf_data *data, int content_len,
								char padding_char, int prefix);
void				pf_apply_precision(t_pf_data *data, int prefix);

int					ft_printf(char *format, ...);
void				pf_apply_flag_hex(t_pf_data *data,
								t_flags flags, t_type type);

#endif

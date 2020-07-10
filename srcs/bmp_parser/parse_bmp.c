/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 19:38:13 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/10 14:40:45 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void		load_header(unsigned int *header, t_engine *eng)
{
	header[0] = 0x42;
	header[1] = 0x4d;
	header[2] = (54) + (eng->buf.size.x * eng->buf.size.y * 3);
	header[3] = 0x0;
	header[4] = 54;
	header[5] = 40;
	header[6] = eng->buf.size.x;
	header[7] = eng->buf.size.y;
	header[8] = 0x1;
	header[9] = 0x18;
	header[10] = 0x0;
	header[11] = eng->buf.size.x * eng->buf.size.y * 3;
	header[12] = 0xEC4;
	header[13] = 0xEC4;
	header[14] = 0x0;
	header[15] = 0x0;
}

static int		write_img_data(t_engine *eng, int fd)
{
	int	col_buf;
	int	x;
	int	y;

	x = 0;
	y = eng->buf.size.y;
	while (y > 0)
	{
		while (x < eng->buf.size.x)
		{
			col_buf = eng->buf.data[x++ + y * eng->buf.size.x];
			write(fd, &col_buf, 3);
		}
		write(fd, "\0\0\0", (4 - (eng->buf.size.x * 3) % 4) % 4);
		x = 0;
		y--;
	}
	return (0);
}

static void		write_file_header(int fd, unsigned int *header)
{
	int		i;

	i = 0;
	while (i < 2)
		write(fd, &header[i++], 1);
	while (i < 8)
		write(fd, &header[i++], 4);
	while (i < 10)
		write(fd, &header[i++], 2);
	while (i < 16)
		write(fd, &header[i++], 4);
}

int				export_frame(t_engine *eng, char *name)
{
	unsigned int	header[16];
	char			*tmp;
	int				fd;
	int				dir_fd;

	if (((dir_fd =
		open("./screenshots", __O_DIRECTORY | O_RDONLY, 00644)) <= 0))
		return (-1);
	close(dir_fd);
	if ((fd = open(\
	tmp = ft_strjoin("./screenshots/", name), O_RDWR | O_CREAT, 00644)) <= 0)
		return (-2);
	free(tmp);
	load_header(header, eng);
	write_file_header(fd, header);
	write_img_data(eng, fd);
	close(fd);
	return (0);
}

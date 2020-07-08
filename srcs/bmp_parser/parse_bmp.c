/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 19:38:13 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/08 14:26:58 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	load_header(unsigned int *header, t_engine *eng)
{
	// FILE HEADER
	header[0] = 0x42;											// 0x42 & 0x4d corresponds to
	header[1] = 0x4d;											// bitmap format prefix ("BM")
	header[2] = (54) + (eng->buf.size.x * eng->buf.size.y * 3); // size of file (header + data)
	header[3] = 0x0;											// always null
	header[4] = 54; 											// header offset (size of header)

	// BITMAP HEADER
	header[5] = 40;												// size of bitmap header
	header[6] = eng->buf.size.x;								// size X of image
	header[7] = eng->buf.size.y;								// size Y of image
	header[8] = 0x1;											// number of planes
	header[9] = 0x18;											// bit per pixel (0x18 corresponds to 24 bits)
	header[10] = 0x0;											// compression method (0 = no compression)
	header[11] = eng->buf.size.x * eng->buf.size.y * 3;			// size of data
	header[12] = 0xEC4;											// horizontal resolution (3780px / meter)
	header[13] = 0xEC4;											// vertical resolution (3780px / meter)
	header[14] = 0x0;											// palette (0 = full palette)
	header[15] = 0x0;											// important colors
}

static int	write_img_data(t_engine *eng, int fd)
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
			// WRITE COLOR : 1 BLOCK OF 3 BYTES
			col_buf = eng->buf.data[x++ + y * eng->buf.size.x];
			write (fd, &col_buf, 3);
		}
		// WRITE PADDING
		write(fd, "\0\0\0", (4 - (eng->buf.size.x * 3) % 4) % 4);
		x = 0;
		y--;
	}
	return (0);
}

static void	write_file_header(int fd, unsigned int *header)
{
	int		i;
	
	// [HEADER] WRITE 2 BLOCKS OF 1 BYTES (BM PREFIX)
	i = 0;
	while (i < 2)
		write(fd, &header[i++], 1);
	// [HEADER] WRITE 6 BLOCKS OF 4 BYTES
	while (i < 8)
		write(fd, &header[i++], 4);
	// [HEADER] WRITE 2 BLOCKS OF 2 BYTES
	while (i < 10)
		write(fd, &header[i++], 2);
	// [HEADER] WRITE 6 BLOCKS OF 4 BYTES
	while (i < 16)
		write(fd, &header[i++], 4);
}

int		export_frame(t_engine *eng, char *name)
{
	unsigned int	header[16];
	char			*tmp;
	int				fd;
	int				dir_fd;
	
	if (((dir_fd =
		open("./screenshots", __O_DIRECTORY | O_RDONLY, 00644)) <= 0))
		return (-1);
	close(dir_fd);
	if((fd = open(tmp = ft_strjoin
		("./screenshots/", name), O_RDWR | O_CREAT, 00644)) <= 0)
		return (-2);
	free(tmp);
	load_header(header, eng);
	write_file_header(fd, header);
	write_img_data(eng, fd);
	close(fd);
	return (0);
}

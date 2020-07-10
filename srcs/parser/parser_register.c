/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_register.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 19:04:02 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/10 18:17:22 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "process.h"

static int		get_direction(char *dir)
{
	if (!ft_strncmp(dir, "NO", 2))
		return (TEX_NORTH);
	if (!ft_strncmp(dir, "SO", 2))
		return (TEX_SOUTH);
	if (!ft_strncmp(dir, "EA", 2))
		return (TEX_EAST);
	if (!ft_strncmp(dir, "WE", 2))
		return (TEX_WEST);
	return (0);
}

static int		parse_line2(t_engine *eng, char *line)
{
	char	**argv;
	int		status;

	status = 0;
	argv = ft_splitcharset(line, ", \t\v\f\r");
	if (ft_strstartswith(line, "RESOLUTION")
	&& (status = check_resolution(argv))
	&& create_window(eng, ft_atoi(argv[1]), ft_atoi(argv[2]), __PROJECT_NAME))
		init_camera(eng, &eng->cam, 80.0F);
	else if (
	ft_strstartswith(line, "CUBE") && (status = check_id_register(argv)))
		register_cube(eng, argv[1], ft_atoi(argv[2]));
	else if (
	ft_strstartswith(line, "SPRITE") && (status = check_id_register(argv)))
		register_sprite(eng, argv[1], ft_atoi(argv[2]));
	else if (ft_strstartswith(line, "CEIL") && (status = check_path(argv)))
		load_from_xpm(argv[1], &eng->tex_ceil, eng);
	else if (ft_strstartswith(line, "FLOOR") && (status = check_path(argv)))
		load_from_xpm(argv[1], &eng->tex_floor, eng);
	ft_freestab(argv);
	return (status);
}

static int		parse_line(t_engine *eng, char *line)
{
	char	**av;
	int		status;

	status = 0;
	av = ft_splitcharset(line, ", \t\v\f\r");
	for(int i = 0; av[i]; i++)
		printf (">> [%s]\n", av[i]);
	if (ft_strncmp(line, "R", 1) == 0 && (status = check_resolution(av))
	&& create_window(eng, ft_atoi(av[1]), ft_atoi(av[2]), __PROJECT_NAME))
		init_camera(eng, &eng->cam, 80.0F);
	else if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
	|| !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2)) &&
	(status = check_path(av)))
		load_from_xpm(av[1], &(eng->textures[get_direction(line)]), eng);
	else if (!ft_strncmp(line, "C", 1) && (status = check_color(av)))
		eng->ceil_col = create_color(ft_atoi(av[1]),
		ft_atoi(av[2]), ft_atoi(av[3]));
	else if (!ft_strncmp(line, "F", 1) && (status = check_color(av)))
		eng->floor_col = create_color(ft_atoi(av[1]),
		ft_atoi(av[2]), ft_atoi(av[3]));
	else if (!ft_strncmp(line, "S", 1) && (status = check_path(av)))
		register_sprite(eng, av[1], 0);
	ft_freestab(av);
	return (status);
}

static t_list	*load_file(char *file)
{
	t_list	*lst;
	t_list	*first;
	int		fd;
	int		status;

	status = 1;
	lst = NULL;
	first = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	while (status > 0)
	{
		if (!first && (first = ft_lstnew("")))
			lst = first;
		else
			ft_lstadd_back(&lst, ft_lstnew(""));
		status = get_next_line(fd, (char **)&ft_lstlast(lst)->content);
	}
	close(fd);
	return (first);
}

void			parse_registry(t_engine *eng, char *file)
{
	t_list	*first;
	t_list	*lines;

	if (!(lines = load_file(file)))
		p_exit(eng, "Can't load map file. aborting.", STATUS_REGISTER_FAILED);
	first = lines;
	if (ft_strendwith(file, ".cub"))
		eng->format = FORMAT;
	else if (ft_strendwith(file, ".cmap"))
		eng->format = CUSTOM_F;
	else
		p_exit(eng, "Invalid map format, aborting.", STATUS_REGISTER_FAILED);
	while (lines)
	{
		if (ft_strlen(lines->content) && !ft_isdigit(*(char *)(lines->content))
			&& *(char *)(lines->content) != ' ')
			if (((eng->format == 1 && !parse_line(eng, (char *)lines->content))
			|| (eng->format == 2 && !parse_line2(eng, lines->content))))
				p_exit(eng,
				"Invalid map line returned a status of 1.", 4);
		lines = lines->next;
	}
	if (eng->format == FORMAT)
		register_cube_format(eng, 1);
	parse_map(eng, first);
}

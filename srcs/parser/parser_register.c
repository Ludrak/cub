/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_register.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:32:21 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/06 15:10:06 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int     parse_line_custom (t_engine *eng, char *line)
{
    char    **argv;
    int     i;
    int     status;

    status = 0;
    argv = ft_splitcharset(line, ", \t\v\f\r");
    if (ft_strstartswith(line, "RESOLUTION") && (status = check_resolution(argv)))
    {
        create_window(eng, ft_atoi(argv[1]), ft_atoi(argv[2]), __PROJECT_NAME);
        init_camera(eng, &eng->cam, 80.0F);
    }
    else if (ft_strstartswith(line, "CUBE") && (status = check_id_register(argv)))
        register_cube(eng, argv[1], ft_atoi(argv[2]));
    else if (ft_strstartswith(line, "SPRITE") && (status = check_id_register(argv)))
        register_sprite(eng, argv[1], ft_atoi(argv[2]));
    else if (ft_strstartswith(line, "CEIL") && (status = check_path(argv)))
        load_from_xpm(argv[1], &eng->cub_tex_ceil, eng);
    else if (ft_strstartswith(line, "FLOOR") && (status = check_path(argv)))
        load_from_xpm(argv[1], &eng->cub_tex_floor, eng);
    i = 0;
    while (argv[i] != NULL)
        free(argv[i++]);
    free(argv);
    return (status);
}

static int     parse_line (t_engine *eng, char *line)
{
    char    **argv;
    int     status;
    int     i;

    status = 0;
    argv = ft_splitcharset(line, ", \t\v\f\r");
    if (ft_strncmp(line, "R", 1) == 0 && (status = check_resolution(argv)))
    {
        create_window(eng, ft_atoi(argv[1]), ft_atoi(argv[2]), __PROJECT_NAME);
        init_camera(eng, &eng->cam, 80.0F);
    }
    else if (!ft_strncmp(line, "NO", 2) && (status = check_path(argv)))
        load_from_xpm(argv[1], &(eng->textures[TEX_NORTH]), eng);
    else if (!ft_strncmp(line, "SO", 2) && (status = check_path(argv)))
        load_from_xpm(argv[1], &(eng->textures[TEX_SOUTH]), eng);
    else if (!ft_strncmp(line, "EA", 2) && (status = check_path(argv)))
        load_from_xpm(argv[1], &(eng->textures[TEX_EAST]), eng);
    else if (!ft_strncmp(line, "WE", 2) && (status = check_path(argv)))
        load_from_xpm(argv[1], &(eng->textures[TEX_WEST]), eng);
    else if (!ft_strncmp(line, "C", 1) && (status = check_color(argv)))
        eng->ceil_col
            = create_color(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]));
    else if (!ft_strncmp(line, "F", 1) && (status = check_color(argv)))
        eng->floor_col
            = create_color(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]));
    else if (!ft_strncmp(line, "S", 1) && (status = check_path(argv)))
        register_sprite(eng, argv[1], 0);
    i = 0;
    while (argv[i] != NULL)
        free(argv[i++]);
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

void    parse_registry(t_engine *eng, char *file)
{
	t_list	*first;
	t_list	*lines;

    if (!(lines = load_file(file)))
		p_exit(eng, "Can't load specified map file. aborting.", STATUS_REGISTER_FAILED);
	first = lines;
    eng->format = 0;
    if (ft_strendwith(file, ".cub"))
        eng->format = FORMAT;
    else if (ft_strendwith(file, ".cmap"))
        eng->format = CUSTOM_F;
    else
        p_exit (eng, "Invalid map format, aborting.", STATUS_REGISTER_FAILED);
    while (lines)
    {
        if (ft_strlen(lines->content) > 0 && !ft_isdigit(*(char *)(lines->content))
            && *(char *)(lines->content) != ' ')
        {
            if (eng->format == FORMAT && !parse_line(eng, (char *)lines->content))
                p_exit (eng, "Invalid map line returned a status of 1.", STATUS_REGISTER_FAILED);
            else if (eng->format == CUSTOM_F && !parse_line_custom(eng, (char *)lines->content))
                p_exit (eng, "Invalid map line returned a status of 1.", STATUS_REGISTER_FAILED);
        }
        lines = lines->next;
    }
    if (eng->format == FORMAT)
		register_cube_format(eng, 1);
    parse_map(eng, first);
}
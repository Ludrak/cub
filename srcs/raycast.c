/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   ((one.end.y) - (one.start.y)): lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:27:57 by lrobino           #+#    #+#             */
/*   Updated: 2020/03/12 15:32:09 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

/**
 *      RETURNS THE INTERSECTION POINT BETWEEN 2 RAYS 
 */
static t_vec2d get_inter(t_ray one, t_ray two)
{
    float b_dot_d_perp = ((one.end.x) - (one.start.x)) * ((two.end.y) - (two.start.y)) - ((one.end.y) - (one.start.y)) * ((two.end.x) - (two.start.x));

    if (b_dot_d_perp == 0)
        return (create_vector(MAX_VIEW, MAX_VIEW));

    float cx = (two.start.x) - (one.start.x);
    float cy = (two.start.y) - (one.start.y);

    float t = (cx * ((two.end.y) - (two.start.y)) - cy * ((two.end.x) - (two.start.x))) / b_dot_d_perp;
    if (t < 0 || t > 1)
        return (create_vector(MAX_VIEW, MAX_VIEW));

    float u = (cx * ((one.end.y) - (one.start.y)) - cy * ((one.end.x) - (one.start.x))) / b_dot_d_perp;
    if (u < 0 || u > 1)
        return (create_vector(MAX_VIEW, MAX_VIEW));


    return (vec_sub(create_vector((one.start.x)+t*((one.end.x) - (one.start.x)), (one.start.y)+t*((one.end.y) - (one.start.y))), one.start));
}

t_cast          perform_raycast(t_player player, t_vec2d r_dir, t_map map)
{
    t_vec2d     cast = create_vector(MAX_VIEW, MAX_VIEW);
    t_ray       ray;
    t_ray       bounds[4];
    int         i;
    int         x;
    int         y;

    if(player.pos.x == floor(player.pos.x)) 
        player.pos.x += 0.001 * r_dir.x;
    if(player.pos.y == floor(player.pos.y)) 
        player.pos.y += 0.001 * r_dir.y;

    ray = create_ray(   create_vector(player.pos.x - floor(player.pos.x),   player.pos.y - floor(player.pos.y)), 
                        create_vector(vec_norm(r_dir).x * 20, vec_norm(r_dir).y * -20));

    bounds[0] = create_ray(create_vector(0, 0), create_vector(1, 0)); // bottom
    bounds[1] = create_ray(create_vector(0, 0), create_vector(0, 1)); // left
    bounds[2] = create_ray(create_vector(1, 1), create_vector(0, 1)); // top
    bounds[3] = create_ray(create_vector(1, 1), create_vector(1, 0)); // right

    x = 0;
    y = 0;
  if (floor(player.pos.x) < map.size_x && floor(player.pos.y) < map.size_y && floor(player.pos.x) > 0 && floor(player.pos.y) > 0)
  {
      //printf ("On The MAP !\n");
        i = 0;
        while (cast.x == MAX_VIEW && cast.y == MAX_VIEW && i < 4)
        {
          cast = get_inter(ray, bounds[i++]);
        }
        if (i == 1)
        {
          x = 0;
          y = -1;
        }
        if (i == 2)
        {
          x = -1;
          y = 0;
        }
        if (i == 3)
        {
          x = 0;
          y = 1;
        }
        if (i == 4)
        {
          x = 1;
          y = 0;
        }
        printf ("x : %f, y : %f\n", cast.x, cast.y);
        printf ("player : x : %f y : %f\n", player.pos.x, player.pos.y);
        printf ("real : x : %f, y : %f\n", cast.x + floor(player.pos.x), cast.y + floor(player.pos.y));

        printf ("%d face\n", i);
        if (i == 5 || (cast.x == 0 && cast.y == 0))
        {
            t_cast out;
            out.dist = 0;
            out.face = 0;
            out.point = create_vector(MAX_VIEW, MAX_VIEW);
            return (out);
        }
        
        //IF BORDER OF OUT OF MAP
        if (floor(player.pos.x + x) >= map.size_x || floor(player.pos.y + y) >= map.size_y || floor(player.pos.x) <= 0 || floor(player.pos.y) <= 0)
        {
            t_cast  out;
            out.point = create_vector(cast.x + player.pos.x, cast.y + player.pos.y);
            return (out);
        } 
        //IF IN
        if(map.map[(int)floor(player.pos.x + x)][(int)floor(player.pos.y + y)] == CUB_BLOCK)
        {
            t_cast  out;
            out.point = create_vector(cast.x + player.pos.x, cast.y + player.pos.y);
            return (out);
        }
        t_player    pl;
        pl.pos = create_vector(cast.x + player.pos.x, cast.y + player.pos.y);
        return (perform_raycast(pl, r_dir, map));
  }
  printf ("Out...\n");
  t_cast out;
  out.point = create_vector(0, 0);;
  return (out);
}

void        cast_to_frame_buffer(t_image *buffer, t_engine engine)
{
    int     i;
    float   angle;
    float   a;
    t_cast  cast;
    
    angle = radians(engine.player.fov) / buffer->size.x;
    a = 0;
    i = 0;
    while (a < radians (engine.player.fov))
    {
        t_vec2d r_dir;
        r_dir.x = sin (a + engine.player.rot);
        r_dir.y = cos (a + engine.player.rot);

        cast = perform_raycast(engine.player, r_dir, engine.map);
        draw_line_to_buffer(buffer, i, vec_mag(cast.point) * 50, create_gray(ft_map(vec_mag(cast.point) * 50, 0, buffer->size.y, 0, 255)));
        i++;
        a += angle;
    }
}
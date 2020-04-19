/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 15:50:28 by coralie           #+#    #+#             */
/*   Updated: 2020/04/19 11:01:51 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

# define NONE -1
# define LEFT 0
# define RIGHT 1
# define TOP 2
# define BOTTOM 3

t_vec2d get_sqinter(t_vec2d pos, t_vec2d dir)
{
  t_vec2d inter = create_vector(0, 0);
  t_vec2d t = create_vector(0, 0);
 
  if ((pos.x < 0) || (pos.x > 1) || (pos.y < 0) || (pos.y > 1))
    return (create_vector(0, 0));
 
  if (dir.x*dir.x + dir.y*dir.y == 0)
    return (create_vector(0, 0));
 
  if (dir.x > 0)
  {
    inter.x = RIGHT;
    t.x = (1 - pos.x) / dir.x;
  } else if (dir.x < 0)
  {
    inter.x = LEFT;
    t.x = (-pos.x) / dir.x;
  } else
    inter.x = -1;
 
  if (dir.y > 0)
  {
    inter.y = TOP;
    t.y = (1 - pos.y) / dir.y;
  } else if (dir.y < 0)
  {
    inter.y = BOTTOM;
    t.y = (-pos.y) / dir.y;
  } else
    inter.y = -1;
 
  if (inter.x == -1 && inter.y == -1)
    return (create_vector(0, 0));
  else if (inter.x == -1)
    return (create_vector(pos.x + t.y * dir.x,
      pos.y + t.y * dir.y));
  else if (inter.y == -1)
    return (create_vector(pos.x + t.x * dir.x,
      pos.y + t.y * dir.y));
  else
  {
    if (t.x < t.y)
      return (create_vector(pos.x + t.x * dir.x,
        pos.y + t.x * dir.y));
    else if (t.x > t.y)
      return (create_vector(pos.x + t.y * dir.x,
        pos.y + t.y * dir.y));
    else
      return (create_vector(pos.x + t.x * dir.x,
        pos.y + t.x * dir.y));
  }
}



t_cast perform_raycast(t_vec2d pos, t_vec2d dir, t_map map)
{
  t_vec2d cast = create_vector(0, 0);
  t_vec2d grid_pos = create_vector(floorf(pos.x), floorf(pos.y));
  t_vec2d relative_pos = create_vector(pos.x - grid_pos.x, pos.y - grid_pos.y);
  t_vec2d real;
 
  if (relative_pos.x == 0.0f && dir.x < 0.0f)
  {
     relative_pos.x = 1.0f;
     grid_pos.x -= 1.0f;
  }
 
  if (relative_pos.y == 0.0f && dir.y < 0.0f)
  {
     relative_pos.y = 1.0f;
     grid_pos.y -= 1.0f;
  }
 
 
  if (grid_pos.x >= 0.0f && grid_pos.x <= map.size_y && grid_pos.y >= 0.0f && grid_pos.y <= map.size_y)
  {
    if (map.map[(int)grid_pos.x][(int)grid_pos.y] == CUB_BLOCK || map.map[(int)grid_pos.x][(int)grid_pos.y] == CUB_VOID)
    {
        t_cast out;
        out.point = pos;
        return (out);
    }
    cast = get_sqinter(relative_pos, dir);
    real = create_vector(grid_pos.x + cast.x, grid_pos.y + cast.y);;
  
    if (real.x >= 0.0f && real.x <= map.size_x && real.y >= 0.0f && real.y <= map.size_y)
    {
      if (map.map[(int)floorf(real.x) - ((cast.x == 0) ? 1 : 0)][(int)floorf(real.y - ((cast.y == 0) ? 1 : 0))] == CUB_BLOCK || map.map[(int)(real.x) - ((cast.x == 0) ? 1 : 0)][(int)(real.y - ((cast.y == 0) ? 1 : 0))] == CUB_VOID)
      {
        t_cast out;
        out.point = real;
        return (out);
      }
      if (map.map[(int)floorf(real.x - ((cast.x == 0) ? 1 : 0))][(int)floorf(real.y - ((cast.y == 0) ? 1 : 0))] == CUB_AIR)
      {
        return (perform_raycast(real, dir, map));
      }
    } else
    {
      t_cast out;
      out.point = pos;
      return (out);
    }
  }
  t_cast out;
  out.point = create_vector(0, 0);
  return (out);
}



void        cast_to_frame_buffer(t_image *buffer, t_engine engine)
{
    int     i;
    float   angle;
    float   a;
    t_cast  cast;
    t_vec2d r_dir;
    
    angle = radians(engine.player.fov) / buffer->size.x;
    a = -radians(engine.player.fov / 2);
    i = 0;
    while (a < radians (engine.player.fov / 2))
    {
        r_dir.x = cos (a + engine.player.rot);
        r_dir.y = sin (a + engine.player.rot);

        cast = perform_raycast(engine.player.pos, r_dir, engine.map);
        cast.point = vec_sub(cast.point, engine.player.pos);
        float h = (VIEW_HEIGHT) / (cos(angle) * vec_mag(cast.point));

        draw_line_to_buffer(buffer, i, h, create_gray(constrain((int)ft_map(h, 0, VIEW_HEIGHT, 0, 255), 0, 255)));
        i++;
        a += angle;
    }
}
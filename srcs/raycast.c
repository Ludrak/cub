/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 15:50:28 by coralie           #+#    #+#             */
/*   Updated: 2020/04/20 19:51:03 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

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
  t_vec2d grid_pos = create_vector((int)(pos.x), (int)(pos.y));
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
 
 
  if (grid_pos.x >= 0.0f && grid_pos.x <= map.size_x && grid_pos.y >= 0.0f && grid_pos.y <= map.size_y)
  {
    if (map.map[(int)grid_pos.x][(int)grid_pos.y] == CUB_BLOCK || map.map[(int)grid_pos.x][(int)grid_pos.y] == CUB_VOID)
    {
        return (create_cast_info(pos, create_vector(pos.x - (int)pos.x, pos.y - (int)pos.y), dir));
    }
    cast = get_sqinter(relative_pos, dir);
    real = create_vector(grid_pos.x + cast.x, grid_pos.y + cast.y);;
  
    if (real.x >= 0.0f && real.x <= map.size_x + 1 && real.y >= 0.0f && real.y <= map.size_y + 1)
    {
      if (map.map[(int)(real.x) - ((cast.x == 0) ? 1 : 0)][(int)(real.y - ((cast.y == 0) ? 1 : 0))] == CUB_BLOCK || map.map[(int)(real.x) - ((cast.x == 0) ? 1 : 0)][(int)(real.y - ((cast.y == 0) ? 1 : 0))] == CUB_VOID)
      {
        return (create_cast_info(real, cast, dir));
      }
      if (map.map[(int)(real.x - ((cast.x == 0) ? 1 : 0))][(int)(real.y - ((cast.y == 0) ? 1 : 0))] == CUB_AIR)
      {
        return (perform_raycast(real, dir, map));
      }
    } else
      return (create_cast_info(pos, cast, dir));
  }
  return (create_cast_info(create_vector(0, 0), create_vector(0, 0), dir));
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

        if (cast.face == TOP)
        	draw_line_to_buffer(buffer, i, h, create_color(ft_constrain((int)ft_map(h, 0, VIEW_HEIGHT, 100, 255), 0, 255), 100, 100));
		else if (cast.face == LEFT)
        	draw_line_to_buffer(buffer, i, h, create_color(100, ft_constrain((int)ft_map(h, 0, VIEW_HEIGHT, 100, 255), 0, 255), 100));
		else if (cast.face == RIGHT)
        	draw_line_to_buffer(buffer, i, h, create_color(100, 100, ft_constrain((int)ft_map(h, 0, VIEW_HEIGHT, 100, 255), 0, 255)));
		else if (cast.face == BOTTOM)
			draw_line_to_buffer(buffer, i, h, create_gray(ft_constrain((int)ft_map(h, 0, VIEW_HEIGHT, 100, 255), 100, 255)));
        i++;
        a += angle;
    }
}
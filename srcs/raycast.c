/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 15:50:28 by coralie           #+#    #+#             */
/*   Updated: 2020/04/25 12:44:17 by lrobino          ###   ########.fr       */
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



t_cast perform_raycast(t_engine *eng, t_vec2d pos, t_vec2d dir, t_map map)
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
    if (map.map[(int)grid_pos.x][(int)grid_pos.y]->id != CUB_AIR)//== CUB_BLOCK || map.map[(int)grid_pos.x][(int)grid_pos.y]->id == CUB_VOID)
    {
        return (create_cast_info(map.map[(int)grid_pos.x][(int)grid_pos.y], pos, create_vector(pos.x - (int)pos.x, pos.y - (int)pos.y), dir));
    }
    cast = get_sqinter(relative_pos, dir);
    real = create_vector(grid_pos.x + cast.x, grid_pos.y + cast.y);;
  
    if (real.x >= 0.0f && real.x <= map.size_x + 1 && real.y >= 0.0f && real.y <= map.size_y + 1)
    {
      if (map.map[(int)(real.x) - ((cast.x == 0) ? 1 : 0)][(int)(real.y - ((cast.y == 0) ? 1 : 0))]->id != CUB_AIR)//== CUB_BLOCK || map.map[(int)(real.x) - ((cast.x == 0) ? 1 : 0)][(int)(real.y - ((cast.y == 0) ? 1 : 0))]->id == CUB_VOID)//CUB_BLOCK CUB_VOID
      {
        return (create_cast_info(map.map[(int)(real.x) - ((cast.x == 0) ? 1 : 0)][(int)(real.y - ((cast.y == 0) ? 1 : 0))], real, cast, dir));
      }
      else//if (map.map[(int)(real.x - ((cast.x == 0) ? 1 : 0))][(int)(real.y - ((cast.y == 0) ? 1 : 0))]->id == CUB_AIR) //CUB_AIR
      {
        return (perform_raycast(eng, real, dir, map));
      }
    } else
      return (create_cast_info(NULL, pos, cast, dir));
  }
  return (create_cast_info(NULL, create_vector(0, 0), create_vector(0, 0), dir));
}



void        cast_to_frame_buffer(t_image *buffer, t_engine *engine)
{
    int     i;
    float   angle;
    float   a;
    t_cast  cast;
    t_vec2d r_dir;

    angle = radians(engine->player.fov) / buffer->size.x;
    a = -radians(engine->player.fov / 2);
    i = 0;
    while (a < radians (engine->player.fov / 2))
    {
        r_dir.x = cos (a + engine->player.rot);
        r_dir.y = sin (a + engine->player.rot);

        cast = perform_raycast(engine, engine->player.pos, r_dir, engine->map);
        cast.point = vec_sub(cast.point, engine->player.pos);
		float h = (VIEW_HEIGHT) / (cos(angle - a) * vec_mag(cast.point));

     /*   if (cast.face == TOP)
        	draw_ray_to_buffer(engine, i, h, engine->cub_tex_top, cast.face_pos, r_dir, cos(angle - a) );
		else if (cast.face == LEFT)
        	draw_ray_to_buffer(engine, i, h, engine->cub_tex_left, cast.face_pos, r_dir, cos(angle - a) );
		else if (cast.face == RIGHT)
        	draw_ray_to_buffer(engine, i, h, engine->cub_tex_right, cast.face_pos, r_dir, cos(angle - a) );
	    else if (cast.face == BOTTOM)
			draw_ray_to_buffer(engine, i, h, engine->cub_tex_bottom, cast.face_pos, r_dir, cos(angle - a) );*/
        draw_ray_to_buffer(engine, i, h, cast.cube->tex, cast.face_pos, r_dir, cos(angle-a));

        i++;
        a += angle;
    }
}
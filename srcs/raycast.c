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
/*static t_vec2d get_inter(t_ray one, t_ray two)
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


    return (create_vector((one.start.x)+t*((one.end.x) - (one.start.x)), (one.start.y)+t*((one.end.y) - (one.start.y))), one.start);
}*/

# define NONE -1
# define LEFT 0
# define RIGHT 1
# define TOP 2
# define BOTTOM 3

// Function ray_rectangle_intersection(x_0, y_0, x_d, y_d, x_min, y_min, x_max, y_max):

//     # Verify rectangle is sane.
//     If (x_min >= x_max) Or (y_min >= y_max):
//         Return BAD_RECTANGLE
//     End If

//     # Verify x_0, y_0 is inside the rectangle.
//     If (x_0 <= x_min) Or (x_0 >= x_max) Or (y_0 <= y_min) Or (y_0 >= y_max):
//         Return OUTSIDE
//     End If

//     # Verify the direction vector is nonzero.
//     If (x_d*x_d + y_d*y_d == 0):
//         Return NO_DIRECTION
//     End If

//     If (x_d > 0):
//         x_intersect = RIGHT
//         t_x = (x_max - x_0) / x_d
//     Else If (x_d < 0):
//         x_intersect = LEFT
//         t_x = (x_min - x_0) / x_d
//     Else:
//         x_intersect = NONE
//     End If

//     If (y_d > 0):
//         y_intersect = TOP
//         t_y = (y_max - y_0) / y_d
//     Else If (y_d < 0):
//         y_intersect = BOTTOM
//         t_y = (y_min - y_0) / y_d
//     Else:
//         y_intersect = NONE
//     End If

//     If (x_intersect == NONE) and (y_intersect == NONE):
//         Return NO_DIRECTION
//     Else If (x_intersect == NONE):
//         Return edge = y_intersect,     # TOP or BOTTOM 
//                   x = x_0 + t_y * x_d,
//                   y = y_0 + t_y * y_d
//     Else If (y_intersect == NONE):
//         Return edge = x_intersect,     # LEFT or RIGHT
//                   x = x_0 + t_x * x_d,
//                   y = y_0 + t_y * y_d
//     Else:
//          If (t_x < t_y):
//              Return edge = x_intersect,  # LEFT or RIGHT
//                        x = x_0 + t_x * x_d,
//                        y = y_0 + t_x * y_d
//          Else If (t_y < t_x):
//              Return edge = y_intersect,  # TOP or BOTTOM
//                        x = x_0 + t_y * x_d,
//                        y = y_0 + t_y * y_d
//          Else:
//              Return corner = y_intersect + x_intersect
//                          x = x_0 + t_x * x_d,
//                          y = y_0 + t_x * y_d
//          End If
//     End If
// End Function
/*
static t_vec2d get_sqinter(t_vec2d pos, t_vec2d dir)
{
  t_vec2d inter;
  t_vec2d t;
 
  if ((pos.x <= 0) || (pos.x >= 1) || (pos.y <= 0) || (pos.y >= 1))
    return (create_vector(0, 0));
 
  if (dir.x*dir.x + dir.y*dir.y == 0)
    return (create_vector(0, 0));
 
  if (dir.x > 0.0f)
  {
    inter.x = RIGHT;
    t.x = (1.0f - pos.x) / dir.x;
  } else if (dir.x < 0.0f)
  {
    inter.x = LEFT;
    t.x = (-pos.x) / dir.x;
  }
  else
    inter.x = -1;
 
  if (dir.y > 0.0f)
  {
    inter.y = TOP;
    t.y = (1.0f - pos.y) / dir.y;
  } else if (dir.y < 0.0f)
  {
    inter.y = BOTTOM;
    t.y = (-pos.y) / dir.y;
  }
  else
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
}*/
 
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
/*
t_cast          perform_raycast(t_player player, t_vec2d r_dir, t_map map)
{
	t_vec2d     cast = create_vector(MAX_VIEW, MAX_VIEW);
	//t_ray       ray;

    if (player.pos.y >= 0 && player.pos.y < map.size_y && player.pos.x >= 0 && player.pos.x < map.size_x)
    {
       // printf ("dir: x:%f, y:%f\n", r_dir.y, r_dir.x);
        t_vec2d pos = create_vector (player.pos.x - floor(player.pos.x), player.pos.y - floor(player.pos.y));
        t_vec2d real;
        // if (pos.x == 0 && r_dir.x < 0)
        // {
        //     pos.x = 1;
        //     player.pos.y--;
        // }
        // if (pos.y == 0 && r_dir.y < 0)
        // {
        //     player.pos.y--;
        //     pos.y = 1;
        // }
        cast = get_sqinter(pos, r_dir);
        real = create_vector (player.pos.x + cast.x, player.pos.y + cast.y);

        if (cast.x == 0 && cast.y == 0)
        {
            t_cast  o;
            o.point = create_vector(0, 0);
            return (o);
        }


        //printf ("cast: x:%f, y:%f\n", cast.y, cast.x);
        //printf ("diff: x:%f, y:%f\n", cast.y - pos.y, cast.x - pos.x);
        //printf ("real: x:%f, y:%f\n", real.y, real.x);
        
        if (floor(real.x) >= 0 && floor(real.y) < map.size_y && floor(real.y) >= 0 && floor(real.x) < map.size_x)
        {
            if (map.map[(int)floor(real.x)][(int)floor(real.y)] == CUB_BLOCK)
            {
                //printf ("\nON BLOCK\nblock : x:%f, y:%f\n", real.x, real.y);
                t_cast out;
                out.point = create_vector(real.x, real.y);
                return (out);
            }
            else if (map.map[(int)floor(real.x)][(int)floor(real.y)] == CUB_AIR)
            {
                //printf ("ON AIR\nblock : x:%f, y:%f\n\n", real.x, real.y);
                t_player pl;
                pl.pos = create_vector(real.x, real.y);
                return (perform_raycast(pl, r_dir, map));
            }
            else
            {
                printf ("OUT OF MAP\n");
                t_cast  o;
                o.point = create_vector(0, 0);
                return (o);
            }
            
        }
    }

    printf ("OUT OF MAP\n");
    t_cast  o;
    o.point = create_vector(0, 0);
    return (o);
}*/

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

/*
t_cast  perform_raycast(t_vec2d pos, t_vec2d dir, t_map map)
{
  t_vec2d cast = create_vector(0, 0);
  t_vec2d relative_pos = create_vector(pos.x - floor(pos.x), pos.y - floor(pos.y));
  

  if (pos.x >= 0 && pos.x < map.size_x && pos.y >= 0 && pos.y < map.size_y)
  {
    if (map.map[(int)floor(pos.x)][(int)floor(pos.y)] == CUB_BLOCK)
    {
        t_cast out;
        out.point = pos;
        return (out);
    }
    cast = get_sqinter(relative_pos, dir);
   
    t_vec2d real = create_vector((float)floor(pos.x) + cast.x, (float)floor(pos.y) + cast.y);;
    if (cast.x == 0)
      real.x -= 0.00001f;
    if (cast.y == 0)
      real.y -= 0.00001f;
 
    if (real.x >= 0 && real.x < map.size_x && real.y >= 0 && real.y < map.size_y)
    {
      if (map.map[(int)floor(real.x)][(int)floor(real.y)] == CUB_BLOCK || map.map[(int)floor(real.x)][(int)floor(real.y)] == CUB_VOID)
      {
        t_cast out;
        out.point = real;
        return (out);
      }
      if (map.map[(int)floor(real.x)][(int)floor(real.y)] == CUB_AIR)
      {
        return (perform_raycast(real, dir, map));
      }
    } else
    {
      t_cast out;
      out.point = create_vector(0, 0);
      return (out);
    }
  }
  t_cast out;
  out.point = create_vector(0, 0);
  return (out);
}*/
 




// t_cast          perform_raycast(t_player player, t_vec2d r_dir, t_map map)
// {
// 	t_cast	out;
//     (void)player;
//     (void)r_dir;
//     (void)map;
// 	/*static t_ray	bounds[4];

// 	bounds[0] = create_ray(create_vector(0, 0), create_vector(1, 0)); // bottom
// 	bounds[1] = create_ray(create_vector(0, 0), create_vector(0, 1)); // left
// 	bounds[2] = create_ray(create_vector(1, 1), create_vector(0, 1)); // top
// 	bounds[3] = create_ray(create_vector(1, 1), create_vector(1, 0)); // right
// 	t_ray			p_dir;

// 	out.point = create_vector(MAX_VIEW, MAX_VIEW);
// 	p_dir = create_ray(create_vector(player.pos.x - floor(player.pos.x), player.pos.y - floor(player.pos.y)),
// 				create_vector(r_dir.x * 20, r_dir.y * 20));

// 	if (floor(player.pos.y) < map.size_x && floor(player.pos.x) < map.size_y && floor(player.pos.x) >= 0 && floor(player.pos.y) >= 0)
// 	{
// 		printf ("IN MAP");
// 		int i = 0;
// 		while (out.point.x == MAX_VIEW && out.point.y == MAX_VIEW && i < 4)
// 		{
// 			out.point = get_inter(p_dir, bounds[i++]);
// 		}
// 		printf ("dir : x:%f y:%f     face:%d", p_dir.end.x, p_dir.end.y, i);
// 		return (out);
// 	}
// 	printf ("OUT MAP");*/
//     printf ("Starting test\n");
//     out.point = get_sqinter(create_vector(0.5, 0.6), create_vector(-1, 0.2));
// 	return (out);
// }

void        cast_to_frame_buffer(t_image *buffer, t_engine engine)
{
    int     i;
    float   angle;
    float   a;
    t_cast  cast;
    t_vec2d r_dir;
    
    angle = radians(engine.player.fov) / buffer->size.x;
    a = 0;
    i = 0;
    while (a < radians (engine.player.fov))
    {
        r_dir.x = cos (a + engine.player.rot);
        r_dir.y = sin (a + engine.player.rot);

        cast = perform_raycast(engine.player.pos, r_dir, engine.map);
        cast.point = vec_sub(cast.point, engine.player.pos);
        float h = (VIEW_HEIGHT) / (cos(angle) * vec_mag(cast.point));

        //TODO ft_constrain(int value, int min, int max);
        draw_line_to_buffer(buffer, i, h, create_gray((h < VIEW_HEIGHT) ? ft_map(h, 0, VIEW_HEIGHT, 0, 255) : 255));
        i++;
        a += angle;
    }
}
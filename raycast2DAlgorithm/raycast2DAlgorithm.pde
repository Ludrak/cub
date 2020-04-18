float x = radians(45);
PVector position = new PVector(3.456478f, 4.56785768f);
 
int  recursion_iterations = 0;
 
int[][] map = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
 
int scale = 50;
 
void setup()
{
  size(1000, 1000);
  noFill();
  strokeWeight(3);
}
 
void draw()
{
  background(255);
 
  translate(250, 250);
  stroke(22);
  strokeWeight(3);
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      fill(255);
      if (map[i][j] == 1)
      {
        fill(32);
      }
      rect(i * scale, j * scale, scale, scale);
    }
  }
 
  noFill();
  stroke(0, 255, 0);
  ellipse(position.x * scale, position.y * scale, 12, 12);
  recursion_iterations = 0;
  strokeWeight(3);
  stroke(255, 0, 0);
  PVector cast = perform_raycast(position, new PVector(sin(x), cos(x)));
  strokeWeight(1);
  ellipse(cast.x * scale, cast.y * scale, 12, 12);
 
  line (position.x * scale, position.y * scale, cast.x * scale, cast.y * scale);
 
  text ("Intersections : " + recursion_iterations, -100, -100);
 
  x+= 0.01;
 
  noStroke();
  fill(150);
  arc (-90, -150, 20, 20, 0, x % TWO_PI, PIE);
 
 
  fill(0);
  text("FPS : " + floor(frameRate), -100, -120);
  noFill();
}
 
public PVector perform_raycast(PVector pos, PVector dir)
{
  PVector cast = new PVector(0, 0);
  PVector grid_pos = new PVector(floor(pos.x), floor(pos.y));
  PVector relative_pos = new PVector(pos.x - grid_pos.x, pos.y - grid_pos.y);
  PVector real;
 
  if (relative_pos.x == 0 && dir.x < 0.0f)
  {
     relative_pos.x = 1;
     grid_pos.x -= 1.0f;
  }
 
  if (relative_pos.y == 0 && dir.y < 0.0f)
  {
     relative_pos.y = 1;
     grid_pos.y -= 1.0f;
  }
 
 
  recursion_iterations++;
  if (grid_pos.x >= 0 && grid_pos.x < 10 && grid_pos.y >= 0 && grid_pos.y < 10)
  {
    if (map[(int)grid_pos.x][(int)grid_pos.y] == 1)
    {
        return (pos);
    }
    cast = get_sqinter(relative_pos, dir);
    real = new PVector(grid_pos.x + cast.x, grid_pos.y + cast.y);;
 
    ellipse(real.x * scale, real.y * scale, 6, 6);
 
    if (real.x >= 0 && real.x < 10 && real.y >= 0 && real.y < 10)
    {
      if (map[floor(real.x) - ((cast.x == 0) ? 1 : 0)][floor(real.y - ((cast.y == 0) ? 1 : 0))] == 1)
      {
        return (real);
      }
      if (map[floor(real.x - ((cast.x == 0) ? 1 : 0))][floor(real.y - ((cast.y == 0) ? 1 : 0))] == 0)
      {
        return (perform_raycast(real, dir));
      }
    } else
    {
      return (pos);
    }
  }
  return (new PVector(0, 0));
}
 
public PVector get_sqinter(PVector pos, PVector dir)
{
  PVector inter = new PVector(0, 0);
  PVector t = new PVector(0, 0);
 
  if ((pos.x < 0) || (pos.x > 1) || (pos.y < 0) || (pos.y > 1))
    return (new PVector(0, 0));
 
  if (dir.x*dir.x + dir.y*dir.y == 0)
    return (new PVector(0, 0));
 
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
    return (new PVector(0, 0));
  else if (inter.x == -1)
    return (new PVector(pos.x + t.y * dir.x,
      pos.y + t.y * dir.y));
  else if (inter.y == -1)
    return (new PVector(pos.x + t.x * dir.x,
      pos.y + t.y * dir.y));
  else
  {
    if (t.x < t.y)
      return (new PVector(pos.x + t.x * dir.x,
        pos.y + t.x * dir.y));
    else if (t.x > t.y)
      return (new PVector(pos.x + t.y * dir.x,
        pos.y + t.y * dir.y));
    else
      return (new PVector(pos.x + t.x * dir.x,
        pos.y + t.x * dir.y));
  }
}

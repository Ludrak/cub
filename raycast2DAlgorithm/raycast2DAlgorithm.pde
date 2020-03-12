
int matrix[][] = {
  {1, 1, 1, 1, 1}, 
  {1, 0, 1, 0, 1}, 
  {1, 0, 0, 0, 0}, 
  {1, 0, 0, 1, 1},
  {1, 0, 0, 0, 0}
};

PVector player = new PVector(2.3, 2.3);

int fov = 80;
float r = 0;


void setup()
{
  stroke(0);
  strokeWeight(3);
  size(600, 600, P2D);
}



void keyPressed()
{
  
}


void draw()
{
  if(keyPressed)
  {
    if(keyCode == LEFT)
      r -= 0.1;
    else if (keyCode == RIGHT)
      r += 0.1;
  }
  translate (50, 50);
  PVector dir = new PVector(mouseX - width / 2 - (player.x - 2) * 100 + 50, -mouseY + height / 2 + (player.y - 2) * 100 - 50);
  PVector cast;
  background(220);
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (matrix[i][j] == 1)
        fill(32);
      else fill(200);
      stroke(20);
      rect(i * 100, j * 100, 100, 100);
      
      //MOUSE
      stroke(255, 255, 0);
      //line(player.x * 100, player.y * 100, player.x * 100 + dir.x * 100, player.y * 100 + dir.y * -100);
    }
  }
  
  float angle = radians(fov) / 1000.0f;
  fill(255, 0, 0, 50);
  beginShape();
  stroke(255, 0, 0);
  for (float a = 0; a < radians(fov); a+=angle)
  {
    cast = perform_raycast(player, new PVector(sin(a + r), cos(a + r)), matrix, 5, 5);
    //println("cast x " + cast.x + " | cast y " + cast.y + " | mouse : " + dir.normalize().x + " ; " + dir.normalize().y  + "\n");
    //line(player.x * 100, player.y * 100, (cast.x) * 100, (cast.y) * 100);
    vertex((cast.x) * 100, (cast.y) * 100);
    //point((cast.x) * 100, (cast.y) * 100);
  }
  fill(255, 100, 0, 50);
  stroke(255, 100, 0);
  vertex((player.x) * 100, (player.y) * 100);
  endShape(CLOSE);
  strokeWeight(10);
  point((player.x) * 100, (player.y) * 100);
  strokeWeight(3);
  
  if (mousePressed)
   {
      player.x = (((float)mouseX + 50)/ (float)width) * 4;
      player.y = (((float)mouseY + 50)/ (float)height) * 4;
   }
}








PVector get_inter(Line one, Line two) 
{
  float x1 = one.get_start().x;
  float y1 = one.get_start().y;
  float x2 = one.get_end().x;
  float y2 = one.get_end().y;

  float x3 = two.get_start().x;
  float y3 = two.get_start().y;
  float x4 = two.get_end().x;
  float y4 = two.get_end().y;

  float bx = x2 - x1;
  float by = y2 - y1;
  float dx = x4 - x3;
  float dy = y4 - y3;

  float b_dot_d_perp = bx * dy - by * dx;

  if (b_dot_d_perp == 0) return null;

  float cx = x3 - x1;
  float cy = y3 - y1;

  float t = (cx * dy - cy * dx) / b_dot_d_perp;
  if (t < 0 || t > 1) return null;

  float u = (cx * by - cy * bx) / b_dot_d_perp;
  if (u < 0 || u > 1) return null;

  return new PVector(x1+t*bx, y1+t*by);
}








PVector  perform_raycast(PVector pos, PVector dir, int map_matrix[][], int map_sx, int map_sy)
{
  PVector cast = null;
  Line    ray;
  Line    bounds[] = new Line[4];
  int     i;
  int     x;
  int     y;
  
  if(pos.x == floor(pos.x)) 
    pos.x += 0.001 * dir.x;
  if(pos.y == floor(pos.y)) 
    pos.y += 0.001 * dir.y;
    
  ray = new Line(new PVector(pos.x - floor(pos.x),   pos.y - floor(pos.y)), 
                 new PVector(dir.normalize().x * 20, dir.normalize().y * -20));

/**  TO FIX CLIPPING AT ABS VALUES
  bounds[0] = new Line(new PVector(-0.5, 0), new PVector(1.5, 0)); // bottom
  bounds[1] = new Line(new PVector(0, -0.5), new PVector(0, 1.5)); // left
  bounds[2] = new Line(new PVector(1.5, 1), new PVector(-0.5, 1)); // top
  bounds[3] = new Line(new PVector(1, 1.5), new PVector(1, -0.5)); // right
*/
  bounds[0] = new Line(new PVector(0, 0), new PVector(1, 0)); // bottom
  bounds[1] = new Line(new PVector(0, 0), new PVector(0, 1)); // left
  bounds[2] = new Line(new PVector(1, 1), new PVector(0, 1)); // top
  bounds[3] = new Line(new PVector(1, 1), new PVector(1, 0)); // right

 
  x = 0;
  y = 0;
  if (floor(pos.x) < map_sx && floor(pos.y) < map_sy && floor(pos.x) > 0 && floor(pos.y) > 0)
  {
    /*  TO FIX CLIPPING AT ABS VALUES
        i = 0;
        PVector smaller = new PVector(100, 100);
        while (i < 4)
        {
          cast = get_inter(ray, bounds[i++]);
          if (cast != null)
            if (mag(cast.x, cast.y) < mag(smaller.x, smaller.y))
              smaller = cast;
        }
        cast = smaller;
        */
        
        i = 0;
        while (cast == null && i < 4)
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
        //println("castX : " + cast.x + " : cast Y : " + cast.y);

        //println(i + " face");
        if (cast == null)
          return (new PVector(0, 0));
        
        //IF BORDER OF OUT OF MAP
        if (floor(pos.x) + x >= map_sx || floor(pos.y) + y >= map_sy || floor(pos.x) <= 0 || floor(pos.y) <= 0)
          return (new PVector(cast.x + floor(pos.x), cast.y + floor(pos.y)));
        if(map_matrix[floor(pos.x) + x][floor(pos.y) + y] == 1)
          return (new PVector(cast.x + floor(pos.x), cast.y + floor(pos.y)));

        return (perform_raycast(new PVector(cast.x + floor(pos.x) + (0.0001 * cast.x), cast.y + floor(pos.y) + (0.0001 * map(cast.y, 0, 1, -1, 1))), dir, map_matrix, map_sx, map_sy));
  }
  return (new PVector(0, 0));
}











class Line
{
  private PVector start;
  private PVector end;

  public Line(PVector start, PVector end)
  {
    this.start = start;
    this.end = end;
  }

  public PVector get_start()
  {
    return (this.start);
  }

  public PVector get_end()
  {
    return(this.end);
  }
}

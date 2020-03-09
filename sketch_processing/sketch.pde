float rotation = 90;
int   view_distance = 5;
 
PVector position = new PVector(6, 4);
float speed = 0.1;
float rot_speed = 2;
 
 
 
 
boolean KEY_UP;
boolean KEY_DOWN;
boolean KEY_LEFT;
boolean KEY_RIGHT;
 
float view_height = 720 * 0.5;
int size = 1;
 
 
int matrix[][] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
 
 
class Line {
  PVector start, end;
 
  Line(PVector _start, PVector _end) {
    start = _start;
    end   = _end;
  }
 
  void set_start(PVector _start) {
    start = _start;
  }
 
  void set_end(PVector _end) {
    end = _end;
  }
 
  PVector get_start() {
    return start;
  }
 
  PVector get_end() {
    return end;
  }
 
  void draw() {
    stroke(0, 100);
    //line(start.x, start.y, end.x, end.y);
  }
 
  PVector line_itersection(Line one, Line two) {
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
 
  PVector intersects_at(Line other) {
    return line_itersection(this, other);
  }
 
  PVector random_bounded_vector() {
    return new PVector(random(width), random(height));
  }
}
Line the_user;
//Line the_others[];
 
 
ArrayList<Line> blocks = new ArrayList<Line>();
 
int NUMBER_OF_OTHERS = 10;
 
void initialize_lines(int x, int y, boolean lines) {
 
  if (lines) {
    //the_others = new Line[NUMBER_OF_OTHERS];
    //for (int i = 0; i < NUMBER_OF_OTHERS; i++) {
    //  the_others[i] = new Line(random_bounded_vector(), random_bounded_vector());
    //}
    for (int j = 0; j < 10; j++)
    {
      for (int i = 0; i < 10; i++)
      {
 
        if (matrix[j][i] == 1)
        {
          blocks.add(new Line(new PVector(i * size, j * size), new PVector(i * size, j * size + size))); // LEFT
          blocks.add(new Line(new PVector(i * size, j * size), new PVector(i * size + size, j * size))); // TOP
          blocks.add(new Line(new PVector(i * size, j * size + size), new PVector(i * size + size, j * size + size))); // BOTTOM
          blocks.add(new Line(new PVector(i * size + size, j * size), new PVector(i * size + size, j * size + size)));
        }
      }
    }
  }
  the_user  = new Line(position, PVector.fromAngle(rotation).normalize());
}
 
void setup() {
  size(1280, 720);
  smooth();
  fill(color(240, 10, 20));
  initialize_lines(0, 0, true);
}
 
void draw() {
  background(0);
  final int nb_ray = width;
  final float fov = radians(80);
  int index = 0;
 
  if (KEY_LEFT)
    rotation-=rot_speed;
  if (KEY_RIGHT)
    rotation += rot_speed;
  if (KEY_UP && can_move(new PVector(cos(radians(rotation)) * 100000, sin(radians(rotation)) * 100000)))
  {
    position.add(PVector.fromAngle(radians(rotation)).normalize().mult(speed));
  }
  if (KEY_DOWN && can_move(new PVector(cos(radians(rotation) + PI) * 100000, sin(radians(rotation) + PI) * 100000)))
  {
    position.sub(PVector.fromAngle(radians(rotation)).normalize().mult(speed));
  }
 
  float angle = fov / nb_ray;
  PVector ray;
  for (float a = -(fov / 2); a < (fov / 2); a+= angle)
  {
    ray = perform_raycast(the_user, the_user.get_start(), new PVector(cos(a + radians(rotation)) * 10000, sin(a + radians(rotation)) * 10000));
 
//float h = (height * 50000) / pow(mag(ray.x, ray.y), 2);
   float h = (view_height) / (cos(a) * mag(ray.x, ray.y));//(height * 10000) / pow(mag(ray.x, ray.y), 2);
    //stroke(map(mag(ray.x, ray.y), 0, view_distance, 255, 10));
    stroke(map(h, 0, view_height, 0, 255));
    line (index, height / 2 + h,
      index, (height / 2) - h);
    index++;
  }
}
 
boolean can_move(PVector direction)
{
  PVector ray = perform_raycast(the_user, the_user.get_start(), direction);
  if (mag(ray.x, ray.y) < speed)
    return (false);
  return (true);
}
 
float  cast_cube(float a)
{
  PVector ray;
  ray = perform_raycast(the_user, the_user.get_start(), new PVector(cos(a + radians(rotation)) * 100000, sin(a + radians(rotation)) * 100000));
 
  //float h = (height * 50000) / pow(mag(ray.x, ray.y), 2);
  float h = (view_height) / (cos (a) * mag(ray.x, ray.y));
  return (h);
}
 
PVector perform_raycast(Line master, PVector pos, PVector dir)
{
  master.set_start(pos);
  master.set_end(dir);
  PVector smaller = new PVector(100000, 100000);
 
  for (int i = 0; i < blocks.size(); i++)
  {
    PVector intersection;
    intersection = master.intersects_at(blocks.get(i));
 
    if (intersection != null)
    {
      //ellipse(intersection.x, intersection.y, 10, 10);
 
      intersection.sub(master.get_start());
      if (ft_mag(intersection.x, intersection.y) < ft_mag(smaller.x, smaller.y))
      {
        smaller = intersection;
      }
    }
    // the_others[i].draw();
  }
 
  return (smaller);
  //the_user.draw();
}
 
float ft_mag(float x, float y)
{
  return (sqrt(x*x + y*y));
}
 
void keyPressed()
{
  if (keyCode == LEFT)
  {
    KEY_LEFT = true;
    //rotation-=rot_speed;
  } else if (keyCode == RIGHT)
  {
    KEY_RIGHT = true;
    //rotation+=rot_speed;
  } else if (keyCode == UP)
  {
    KEY_UP = true;
    //position.add(PVector.fromAngle(radians(rotation)).normalize().mult(speed));
  } else if (keyCode == DOWN)
  {
    KEY_DOWN = true;
    //position.sub(PVector.fromAngle(radians(rotation)).normalize().mult(speed));
  }
  initialize_lines((int) position.x, (int) position.y, false);
}
 
void keyReleased()
{
  if (keyCode == LEFT)
    KEY_LEFT = false;
  else if (keyCode == RIGHT)
    KEY_RIGHT = false;
  else if (keyCode == UP)
    KEY_UP = false;
  else if (keyCode == DOWN)
    KEY_DOWN = false;
}

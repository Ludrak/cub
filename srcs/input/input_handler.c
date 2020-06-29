
# include "engine.h"

void    handle_input(t_engine *eng)
{
    if (eng->keys.left.pressed)
		eng->player.rot += 0.09f;
	
    if (eng->keys.right.pressed)
		eng->player.rot -= 0.09f;

	// Since modulo doesnt work for float we need to bound this into [0;TWO_PI] 
	if (eng->player.rot > TWO_PI)
		eng->player.rot = 0;
	else if (eng->player.rot < 0)
		eng->player.rot = TWO_PI;

    ft_constrain(eng->player.rot , 0, TWO_PI);

	if (eng->keys.up.pressed)
    {
		eng->player.vel.x = -cos(eng->player.rot) * eng->player.speed * 0.01f;
		eng->player.vel.y = -sin(eng->player.rot) * eng->player.speed * 0.01f;

		if (eng->map.map[(int)floorf(eng->player.pos.x + eng->player.vel.x * 10.0f)][((int)floorf(eng->player.pos.y))]->id == CUB_AIR)
			eng->player.pos.x += eng->player.vel.x;
		if (eng->map.map[(int)floorf(eng->player.pos.x)][((int)floorf(eng->player.pos.y + eng->player.vel.y * 10.0f))]->id == CUB_AIR)
			eng->player.pos.y += eng->player.vel.y;
    }

    if (eng->keys.down.pressed)
	{
		eng->player.vel.x = cos(eng->player.rot) * eng->player.speed * 0.01f;
		eng->player.vel.y = sin(eng->player.rot) * eng->player.speed * 0.01f;

		if (eng->map.map[(int)floorf(eng->player.pos.x + eng->player.vel.x * 10.0f)][((int)floorf(eng->player.pos.y))]->id == CUB_AIR)
			eng->player.pos.x += eng->player.vel.x;
		if (eng->map.map[(int)floorf(eng->player.pos.x)][((int)floorf(eng->player.pos.y + eng->player.vel.y * 10.0f))]->id == CUB_AIR)
			eng->player.pos.y += eng->player.vel.y;
    }
}
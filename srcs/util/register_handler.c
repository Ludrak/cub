
# include "engine.h"

void    register_cubes(t_engine *eng)
{
    eng->cubes = NULL;
    register_cube(eng, NULL, CUB_VOID);
	register_cube(eng, NULL, CUB_AIR);
	register_cube(eng, "res/textures/dungeon_wall.xpm", CUB_BLOCK);
	register_cube(eng, "res/textures/dungeon_wall_torch.xpm", CUB_BLOCK_TORCH);
	register_cube(eng, "res/textures/dungeon_wall_cracked.xpm", CUB_BLOCK_CRACKED);
}

void    register_sprites(t_engine *eng)
{
    eng->loaded_sprites = NULL;
    eng->sprites = NULL;
    register_sprite(eng, "res/textures/phantom.xpm", 0);
}
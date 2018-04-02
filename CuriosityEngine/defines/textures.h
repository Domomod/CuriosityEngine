#ifndef TEXTURES_H
#define TEXTURES_H

#include "../texture.h"
#include "../simpleTexture.h"
#include "../texturepack.h"

namespace Textures
{
    static Texture grass;
    static Texture stone;
    static Texture dirt;
    static Texture flowers;

    static Texture tree1;
    static Texture tree2;
    static Texture tree3;
    static Texture fallen_tree1;

    static Texture fern_1;
    static Texture flower_1;


    static Texture house;
    static Texture barrel;

    static Texture stone_bricks;
    static Texture stone_tiles;
    static Texture stone_decoration;

    static Texture torch;
    static Texture wood;
    static Texture wood_log;

    static Texture crystal;
    static Texture rpg_wall;
    static Texture shiny_tiles;

    static Texture bricks;
    static Texture bricks2;
    static Texture bricks3;


    static SimpleTexture blendMap;
    static SimpleTexture heightMap;

    static TexturePack terrainTextures(&Textures::grass, &Textures::dirt, &Textures::flowers, &Textures::stone, &Textures::blendMap);
    inline void Load()
    {
        Textures::grass.LoadTexture("./res/textures/grass.png");
        Textures::stone.LoadTexture("./res/textures/stone.jpg", "./res/textures/stone_normal.png", "./res/textures/stone_disp.png");
        Textures::dirt.LoadTexture("./res/textures/dirt.png");
        Textures::flowers.LoadTexture("./res/textures/grassFlowers.png");

        Textures::tree1.LoadTexture("./res/textures/tree_1.png");
        Textures::tree1.setTransparency(true);
        Textures::tree2.LoadTexture("./res/textures/lowPolyTree.png", "./res/textures/default_normal.png", "./res/textures/default_disp.png");
        Textures::tree3.LoadTexture("./res/textures/brown.png");
        Textures::fallen_tree1.LoadTexture("./res/textures/fallen_tree_1.png", "./res/textures/fallen_tree_1_normal.png", "./res/textures/default_disp.png");

        Textures::fern_1.LoadTexture("./res/textures/fern_1.png");
        Textures::fern_1.setTransparency(true);
        Textures::flower_1.LoadTexture("./res/textures/flower_1.png");
        Textures::flower_1.setTransparency(true);

        Textures::house.LoadTexture("./res/textures/house.png");
        Textures::barrel.LoadTexture("./res/textures/barrel.png");

        Textures::stone_bricks.LoadTexture("./res/textures/bricks.jpg", "./res/textures/bricks_normal.jpg", "./res/textures/bricks_disp.png");
        Textures::stone_tiles.LoadTexture("./res/textures/stone_tiles.jpg", "./res/textures/stone_tiles_normal.jpg");
        Textures::stone_decoration.LoadTexture("./res/textures/decoration.jpg", "./res/textures/decoration_normal.jpg", "./res/textures/decoration_disp.jpg");

        Textures::torch.LoadTexture("./res/textures/torch.jpg");
        Textures::wood.LoadTexture("./res/textures/wood.jpg" , "./res/textures/wood_normal.png", "./res/textures/wood_disp2.jpg" );
        Textures::wood_log.LoadTexture("./res/textures/wood_log.jpg" , "./res/textures/wood_log_normal.jpg");

        Textures::crystal.LoadTexture("./res/textures/chrome.jpg", "./res/textures/default_normal.jpg");
        Textures::rpg_wall.LoadTexture("./res/textures/rpg_wall.jpg", "./res/textures/rpg_wall_normal.png", "./res/textures/rpg_wall_disp1.jpg");
        Textures::shiny_tiles.LoadTexture("./res/textures/shiny_tiles.jpg", "./res/textures/shiny_tiles_normal.jpg", "./res/textures/shiny_tiles_disp.jpg");

        Textures::bricks.LoadTexture("./res/textures/bricks2.jpg", "./res/textures/bricks2_normal.jpg", "./res/textures/bricks2_disp.jpg");
        Textures::bricks2.LoadTexture("./res/textures/bricks3.jpg", "./res/textures/bricks3_normal.jpg","./res/textures/bricks3_disp.jpg");
        Textures::bricks3.LoadTexture("./res/textures/bricks4.jpg", "./res/textures/bricks4_normal.png", "./res/textures/bricks4_disp.png");

        Textures::blendMap.LoadTexture("./res/textures/blendMap.png");
        Textures::heightMap.LoadTexture("./res/textures/heightMap.png");
    }
}
#endif // TEXTURES_H

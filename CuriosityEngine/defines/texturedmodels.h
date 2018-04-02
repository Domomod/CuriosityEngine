#ifndef TEXTUREDMODELS_H
#define TEXTUREDMODELS_H

#include "materials.h"
#include "textures.h"
#include "meshes.h"
namespace TexturedModels
{
    static TexturedModel monkey_model;
    static TexturedModel entity1_model;
    static TexturedModel entity2_model;

    static TexturedModel tree1_model;
    static TexturedModel tree2_model;
    static TexturedModel dead_tree_1_model;
    static TexturedModel dead_tree_2_model;
    static TexturedModel fallen_tree1_model;
    static TexturedModel tree_stump_1_model;

    static TexturedModel fern_1_model;
    static TexturedModel flower_1_model;

    static TexturedModel barrel_model;
	static TexturedModel sphere_model;
	static TexturedModel quad_model;

    inline void Load()
    {
        TexturedModels::monkey_model.LoadTexturedModel(&Meshes::mesh3, &Textures::crystal, &emerald);
        TexturedModels::entity1_model.LoadTexturedModel(&Meshes::ground, &Textures::stone, &stone);
        TexturedModels::entity2_model.LoadTexturedModel(&Meshes::wall1, &Textures::stone, &stone);
        TexturedModels::tree1_model.LoadTexturedModel(&Meshes::tree1, &Textures::tree1, &simple);
        TexturedModels::tree2_model.LoadTexturedModel(&Meshes::tree2, &Textures::tree1, &simple);
        TexturedModels::dead_tree_1_model.LoadTexturedModel(&Meshes::dead_tree_1, &Textures::tree1, &simple);
        TexturedModels::dead_tree_2_model.LoadTexturedModel(&Meshes::dead_tree_2, &Textures::tree1, &simple);
        TexturedModels::fallen_tree1_model.LoadTexturedModel(&Meshes::fallen_tree1, &Textures::fallen_tree1, &simple);
        TexturedModels::tree_stump_1_model.LoadTexturedModel(&Meshes::tree_stump_1, &Textures::fallen_tree1, &simple);
        TexturedModels::fern_1_model.LoadTexturedModel(&Meshes::fern_1, &Textures::fern_1, &simple);
        TexturedModels::flower_1_model.LoadTexturedModel(&Meshes::flower_1, &Textures::flower_1, &simple);
        TexturedModels::barrel_model.LoadTexturedModel(&Meshes::barrel, &Textures::barrel, &simple);
		TexturedModels::sphere_model.LoadTexturedModel(&Meshes::sphere, &Textures::crystal, &simple);
		TexturedModels::quad_model.LoadTexturedModel(&Meshes::quad, &Textures::crystal, &simple);
    }
}

#endif // TEXTUREDMODELS_H

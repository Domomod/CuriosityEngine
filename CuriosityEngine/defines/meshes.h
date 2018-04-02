#ifndef MESHES_H
#define MESHES_H

namespace Meshes
{
    static Mesh tree1;
    static Mesh tree2;
    static Mesh dead_tree_1;
    static Mesh dead_tree_2;
    static Mesh fallen_tree1;
    static Mesh tree_stump_1;

    static Mesh fern_1;
    static Mesh flower_1;

    static Mesh mesh3;
    static Mesh barrel;
	static Mesh sphere;
	static Mesh quad;

    static Mesh wall1;
    static Mesh wall2;
    static Mesh wall3;
    static Mesh wall4;

    static Mesh ground;
    static Mesh celling;

    inline void Load()
    {
        Meshes::tree1.LoadMesh("./res/OBJ/tree_1.obj");
        Meshes::tree2.LoadMesh("./res/OBJ/tree_2.obj");
        Meshes::dead_tree_1.LoadMesh("./res/OBJ/dead_tree_1.obj");
        Meshes::dead_tree_2.LoadMesh("./res/OBJ/dead_tree_2.obj");
        Meshes::fallen_tree1.LoadMesh("./res/OBJ/fallen_tree_1.obj");
        Meshes::tree_stump_1.LoadMesh("./res/OBJ/tree_stump_1.obj");

        Meshes::fern_1.LoadMesh("./res/OBJ/fern_1.obj");
        Meshes::flower_1.LoadMesh("./res/OBJ/flower_1.obj");

        Meshes::mesh3.LoadMesh("./res/OBJ/monkey3.obj");
        Meshes::barrel.LoadMesh("./res/OBJ/barrel.obj");
		Meshes::sphere.LoadMesh("./res/OBJ/sphere.obj");
		Meshes::quad.LoadMesh("./res/OBJ/quad.obj");

        Meshes::wall1.LoadMesh("./res/OBJ/verticalPlane.obj");
        Meshes::wall2.LoadMesh("./res/OBJ/verticalPlane2.obj");
        Meshes::wall3.LoadMesh("./res/OBJ/verticalPlane3.obj");
        Meshes::wall4.LoadMesh("./res/OBJ/verticalPlane4.obj");

        Meshes::ground.LoadMesh("./res/OBJ/plane.obj");
        Meshes::celling.LoadMesh("./res/OBJ/plane2.obj");
    }
}

#endif // MESHES_H

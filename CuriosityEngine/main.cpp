#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <vector>
#include <time.h>

#include "display.h"
#include "masterrenderer.h"

#include "mesh.h"
#include "texturedmodel.h"
#include "entity.h"
#include "terrain.h"

#include "texture.h"
#include "simpleTexture.h"
#include "texturepack.h"

#include "transform.h"
#include "camera.h"
#include "input.h"
#include "sdl_backend.h"
#include "mytime.h"

#include "light.h"

#include "windows.h"

#include "entityloader.h"

#include "player.h"

//deklaracja danych
#include "defines/materials.h"
#include "defines/textures.h"
#include "defines/meshes.h"
#include "defines/texturedmodels.h"



//ToDo: ogarnij te zmienne globalne
bool m_mouseLocked;
glm::vec3 playerForward;
const glm::vec3 playerUp = glm::vec3(0.0f, 1.0f, 0.0f);
int camera_mode=1;
int camera_switch_cd=0;

enum Models
{
    Tree1,
    Tree2
};

void GenerateObjects(const std::string& fileName, Terrain terrain)
{
    std::fstream file;
    file.open(fileName);
    for(int num = 0; num < 400; num++)
    {
        int model = rand() % 8;

        float pos_x= (rand() % 16000)/10;
        float pos_z= (rand() % 16000)/10;
        float pos_y = terrain.GetHeight(pos_x, pos_z);

        float rot_x=0;
        float rot_y = rand() % 360;
        float rot_z=0;

        float scale = 1;
        if(model==0) scale= (rand() % 10 + 60)/10;
        if(model==1) scale= (rand() % 20 + 60)/10;
        if(model==2) scale= (rand() % 15 + 35)/10;
        if(model==3) scale= (rand() % 25 + 45)/10;
        if(model==4) scale= (rand() % 60 + 160)/10;
        if(model==5) scale= (rand() % 40 + 100)/10;
        if(model==6) scale= (rand() % 40 + 100)/10;
        if(model==7) scale= (rand() % 60 + 140)/10;

        file << model << " ";

        file << pos_x << " ";
        file << pos_y << " ";
        file << pos_z << " ";

        file << rot_x << " ";
        file << rot_y << " ";
        file << rot_z << " ";

        file << scale << std::endl;
    }
}
namespace EntityLoader
{
	Entity create()
	{
		return Entity(TexturedModels::tree1_model, glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	}

	void load(std::vector <Entity> &entites_list)
	{
		entites_list.push_back(Entity(TexturedModels::tree1_model, glm::vec3(10.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 5.0f));
		entites_list.push_back(Entity(TexturedModels::tree1_model, glm::vec3(10.0f, 0.0f, 10.0f), 0.0f, 0.0f, 0.0f, 4.0f));
		entites_list.push_back(Entity(TexturedModels::tree1_model, glm::vec3(10.0f, 0.0f, 20.0f), 0.0f, 0.0f, 0.0f, 6.0f));
	}

	TexturedModel choose_model(int num)
	{
		if (num == 0)
			return TexturedModels::fallen_tree1_model;
		if (num == 1)
			return TexturedModels::tree_stump_1_model;
		if (num == 2)
			return TexturedModels::fern_1_model;
		if (num == 3)
			return TexturedModels::flower_1_model;
		if (num == 4)
			return TexturedModels::tree1_model;
		if (num == 5)
			return TexturedModels::tree2_model;
		if (num == 6)
			return TexturedModels::dead_tree_1_model;
		if (num == 7)
			return TexturedModels::dead_tree_2_model;
		else
			return TexturedModels::monkey_model;
	}

	void load2(std::vector <Entity> &entites_list, const std::string& fileName, Terrain &terrain)
	{
		std::fstream file;
		file.open(fileName);
		while (file.good())
		{
			int model;

			float pos_x;
			float pos_y;
			float pos_z;

			float rot_x;
			float rot_y;
			float rot_z;

			float scale;

			file >> model;

			file >> pos_x;
			file >> pos_y;
			file >> pos_z;


			file >> rot_x;
			file >> rot_y;
			file >> rot_z;

			file >> scale;

			pos_y = terrain.GetHeight(pos_x, pos_z);
			if (model == 0) pos_y += 5.0f;
			if (model == 4 || 5 || 6 || 7) pos_y -= 5.0f;

			entites_list.push_back(Entity(choose_model(model), glm::vec3(pos_x, pos_y, pos_z), rot_x, rot_y, rot_z, scale));
		}
		file.close();
	}
}

int main(int argc, char *argv[])
{
    AllocConsole();
    freopen("CONOUT$", "a", stdout);

    srand (time(NULL));

    std::cout<<"siema"<<std::endl;
    Display display(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World");

    Input input;

    Transform transform;
    
    m_mouseLocked = false;

    Textures::Load();
    Meshes::Load();
    TexturedModels::Load();

	Entity sphere(TexturedModels::sphere_model, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	Entity rectangle(TexturedModels::quad_model, glm::vec3(0.0f, 180.0f, 0.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	Entity barrel(TexturedModels::barrel_model, glm::vec3(10.0f,0.0f,10.0f), 0.0f, -135.0f, 0.0f, 3.0f);
    Player player(&barrel);

    Entity monkey(TexturedModels::monkey_model, glm::vec3(1600.0f,120.0f,800.0f), 0.0f, -135.0f, 0.0f, 100.0f);
    Entity fallen_tree(TexturedModels::entity2_model, glm::vec3(60.0f,0.0f,60.0f), 0.0f, -135.0f, 0.0f, 10.0f);
    Entity light(TexturedModels::monkey_model, glm::vec3(120.0f,0.0f,120.0f), 0.0f, -135.0f, 0.0f, 0.5f);
    Entity light2(TexturedModels::monkey_model, glm::vec3(800.0f,200.0f,800.0f), 0.0f, -135.0f, 0.0f, 1.5f);
//    Entity entity1(entity1_model, glm::vec3(0.0f,0.0f,0.0f), 0.0f, 0.0f, 0.0f, 1.0f);
//    Entity entity2(TexturedModels::entity2_model, glm::vec3(10.0f,-1.0f,10.0f), 0.0f, -90.0f, 0.0f, 10.0f);

    std::vector<Entity> entities;
//
    //entities.push_back(monkey);
    entities.push_back(light);
    entities.push_back(light2);
    entities.push_back(fallen_tree);
//    entities.push_back(entity2);


    //test->push_back(Entity(TexturedModels::tree1_model,glm::vec3(30,1.0f,100), 0.0f, -90.0f, 0.0f, 10.0f));

    Camera camera(glm::vec3(30,0,30), 70.0f, (float)display.GetWindowWidth()/(float)display.GetWindowHeight(), 1.0f, 2000.0f);
    //Transform transform;
    camera.setFocusPoint(player.playerEntity->GetPosAdr());

    Terrain terrain(60,60,glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f,Textures::terrainTextures, stone);

	std::vector<Light> lights;
	lights.push_back(Light(DIRECTIONAL_LIGHT, glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.0f, glm::vec3(0.1f), 0.2f));
	for (int j = 0; j < 100; j++)
	{
		glm::vec3 red =		glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 green =	glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 blue =	glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 violet =	glm::vec3(1.0f, 0.0f, 1.0f);
		glm::vec3 yellow =	glm::vec3(1.0f, 1.0f, 0.0f);
		glm::vec3 cyan =	glm::vec3(0.0f, 1.0f, 1.0f);

		glm::vec3* whichColor[] = { &red,&green,&blue,&violet,&yellow,&cyan };

		float pos_x = (rand() % 16000) / 10;
		float pos_z = (rand() % 16000) / 10;
		float pos_y = terrain.GetHeight(pos_x, pos_z) + 6.0f;
		lights.push_back(Light(	POINT_LIGHT,
								glm::vec3(pos_x, pos_y, pos_z),
								1.0f, 0.0f, 0.001f, // completely fades after  units
								*whichColor[rand() % 6],
								0.05f));
	}

    std::vector<Terrain> terrains;
    terrains.push_back(terrain);
//    TerrainRenderer terrainRenderer;
//    EntityRenderer entityRenderer;
    MasterRenderer masterRenderer(&rectangle ,&sphere);

    int counter = 0;
    double time_counter = 0.0f;

    //initialize the time class
    MyTime::initialize();

//    GLuint *data;
    //GenerateObjects("world/objects.txt", terrain);

    //EntityLoader::load(entities);
    EntityLoader::load2(entities, "world/objects.txt", terrain);

    entities.push_back(barrel);
	
	int seconds = 0;
	while(!display.IsClosed())
    {
        MyTime::update();
        input.update();

		player.Input(terrain);
        playerForward=glm::vec3(
                                camera.getForward().x,
                                0,
                                camera.getForward().z
                                );
		camera.Input();
		entities.pop_back();
        entities.push_back(*(player.playerEntity));

        if(SDLGetIsCloseRequested())
            display.Close();

        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		float t = seconds * M_PI / 180;
		lights[0].m_ambientCoefficient = 0.4f + 0.35f*sin(t);
		lights[0].m_color = glm::vec3(powf(sin(t),0.3f),sin(t),sin(t));
		lights[0].m_posdir= glm::vec3(0.5f * cos(t),
			-sin(t),
			sin(t));
		if (seconds >= 180 or seconds == 0)
		{
			lights[0].m_color = glm::vec3(0.0f);
			lights[0].m_posdir = glm::vec3(0.0f);
		}  
		//lights[1].m_position = player.GetPos();

        masterRenderer.Render(entities, terrains, lights, camera);

        display.Update();
        time_counter += MyTime::getDelta();
        counter ++;

        if (time_counter > 1.0f)
        {	
			seconds += 1;
            std::cout<<"fps: "<<counter<<std::endl;
            counter=0;
            time_counter=0.0f;
        }
    
		if (seconds == 360)
			seconds = 0;
	}
    return 0;
}

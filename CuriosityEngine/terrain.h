#ifndef TERRAIN_H
#define TERRAIN_H

#include "mesh.h"
#include "texturepack.h"

static const float TERRAIN_SIZE = 1600;
static const int VERTEX_COUNT = 128;

class Terrain
{
public:
    Terrain(int gridX, int gridZ, glm::vec3 pos, glm::vec3 rot, float scale, TexturePack &texture_pack, Material &material)
    {
        this->m_texture_pack = &texture_pack;
        this->m_x = gridX * TERRAIN_SIZE;
        this->m_z = gridZ * TERRAIN_SIZE;
		this->m_pos = pos;
		this->m_rot = rot;
		this->m_scale = scale;
        this->m_material = &material;
        generateTerrain();
    }
    virtual ~Terrain();

	inline glm::vec3 GetPos() { return m_pos; }

	inline glm::vec3 GetRotXYZ() { return m_rot; }

	inline float GetScale() { return m_scale; }

    inline float& GetX() { return m_x; }

    inline float& GetZ() { return m_z; }

    inline Mesh* GetRawModel() { return m_model; }

    inline TexturePack* GetTexture() { return m_texture_pack; }

    inline Material* GetMaterial() { return m_material; }

    float GetHeight(float x, float z);

protected:

private:
    void generateTerrain();

    float heights[VERTEX_COUNT+1][VERTEX_COUNT+1];
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	float m_scale = 1.0f;

    float m_x;
    float m_z;
    Mesh *m_model;
    TexturePack *m_texture_pack;
    Material *m_material;
};

#endif // TERRAIN_H

#ifndef MATERIALS_H
#define MATERIALS_H

//#include "../entitiesdefine.h" // <- pozwala na includowanie z innych subfolderow
#include "../material.h"

static Material simple (
    glm::vec3(0.2f, 0.2f, 0.2f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    6.0f,
    0.0f,
    0.0f
    );

static Material emerald (
    glm::vec3(0.02f, 0.2f, 0.02f),
    glm::vec3(0.07568f, 0.61424f, 0.07568f),
    glm::vec3(0.633f, 0.727811f, 0.633f),
    6.0f,
    0.0f,
    0.0f
    );

static Material shiny_tiles (
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    16.0f,
    0.07f,
    -0.2f
    );

static Material stone_bricks(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.03f,
    -0.15f
);

static Material stone(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.15f,
    -0.15f
);

static Material stone_tiles(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.015f,
    -0.5f
);
static Material stone_decoration(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.015f,
    0.0f
);

static Material wood(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.015f,
    -0.5f
);
static Material wood_log(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.01f,
    -1.0f
);

static Material torch(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    0.0f,
    0.00f,
    0.0f
);

static Material rpg_wall(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.04f,
    -0.15f
);

static Material bricks(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.045f,
    -0.5f
);
static Material bricks2(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.055f,
    -0.5f
);
static Material bricks3(
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    1.0f,
    0.015f,
    -0.0f
);

#endif // MATERIALS_H
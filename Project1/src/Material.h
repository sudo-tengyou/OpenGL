#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "Texture.h"

class Material {
public:
    Material(float sh = 0.0f, glm::vec3 a = glm::vec3(), glm::vec3 d = glm::vec3(), glm::vec3 s = glm::vec3());
    const glm::vec3& getAmb() const;
    const glm::vec3& getDiffu() const;
    const glm::vec3& getSpecu() const;
    float getShini() const;
private:
    float shininess;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif // !MATERIAL_H
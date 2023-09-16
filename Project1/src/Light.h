#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    Light(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s);
    const glm::vec3& getPos() const;
    const glm::vec3& getAmb() const;
    const glm::vec3& getDiffu() const;
    const glm::vec3& getSpecu() const;
private:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif // !LIGHT_H
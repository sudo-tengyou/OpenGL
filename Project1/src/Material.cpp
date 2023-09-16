#include "Material.h"

Material::Material(float sh, glm::vec3 a, glm::vec3 d, glm::vec3 s): shininess(sh), ambient(a), diffuse(d), specular(s)
{
}


const glm::vec3& Material::getAmb() const
{
	return ambient;
}

const glm::vec3& Material::getDiffu() const
{
	return diffuse;
}

const glm::vec3& Material::getSpecu() const
{
	return specular;
}

float Material::getShini() const
{
	return shininess;
}

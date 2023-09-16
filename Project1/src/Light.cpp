#include "Light.h"

Light::Light(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s): position(p), ambient(a), diffuse(d), specular(s)
{
}

const glm::vec3& Light::getPos() const
{
	return position;
}

const glm::vec3& Light::getAmb() const
{
	return ambient;
}

const glm::vec3& Light::getDiffu() const
{
	return diffuse;
}

const glm::vec3& Light::getSpecu() const
{
	return specular;
}

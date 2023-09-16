#include "Texture.h"

Texture::Texture(const char* path, unsigned int textUnit, std::string type, GLenum colorFormat,
	GLenum texType, GLint sWrap, GLint tWrap, GLint minFilter, GLint magFilter):
	textureType(texType), textureUnit(textUnit), type(type)
{
	GLCHECK(glGenTextures(1, &textureID));
	GLCHECK(glActiveTexture(GL_TEXTURE0 + textUnit));
	GLCHECK(glBindTexture(texType, textureID));

	GLCHECK(glTexParameteri(texType, GL_TEXTURE_WRAP_S, sWrap));
	GLCHECK(glTexParameteri(texType, GL_TEXTURE_WRAP_T, tWrap));
	GLCHECK(glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, minFilter));
	GLCHECK(glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, magFilter));

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLCHECK(glTexImage2D(texType, 0, GL_RGB, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data));
		GLCHECK(glGenerateMipmap(texType));
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		exit(0);
	}
	stbi_image_free(data);
}

void Texture::Bind()
{
	GLCHECK(glActiveTexture(GL_TEXTURE0 + textureUnit));
	GLCHECK(glBindTexture(textureType, textureID));
}

void Texture::UnBind()
{
	GLCHECK(glActiveTexture(GL_TEXTURE0 + textureUnit));
	GLCHECK(glBindTexture(textureType, 0));
}

std::string Texture::getType() const {
	return type;
}

unsigned int Texture::getID() const {
	return textureID;
}

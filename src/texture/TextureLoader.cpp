#include <texture/OpenGLTexture.h>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <stdexcept>

OpenGLTexture::OpenGLTexture(const char* path)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_data = stbi_load(path, &m_width, &m_height, &nrChannels, 0);
	if (!m_data)
	{
		throw std::runtime_error("Failed to load texture!");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(m_data);
}

int OpenGLTexture::getWidth() const
{
	return m_width;
}

int OpenGLTexture::getHeight() const
{
	return m_height;
}

int OpenGLTexture::getNrChannels() const
{
	return nrChannels;
}

unsigned int OpenGLTexture::getTextureID() const
{
	return m_textureID;
}

unsigned char* OpenGLTexture::getData() const
{
	return m_data;
}

void OpenGLTexture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void OpenGLTexture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
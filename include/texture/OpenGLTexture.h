#pragma once

class OpenGLTexture {
private:
	int m_width;
	int m_height;
	int nrChannels;

	unsigned int m_textureID;
	unsigned char* m_data;

public:
	OpenGLTexture(const char* path);

	int getWidth() const;
	int getHeight() const;
	int getNrChannels() const;
	unsigned int getTextureID() const;

	unsigned char* getData() const;

	void bind() const;
	void unbind() const;

};
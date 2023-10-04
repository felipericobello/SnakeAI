#include "Texture2D.h"


Texture2D::Texture2D(std::string& filepath)
	: m_RendererID(0), m_Filepath(filepath), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 0);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, m_LocalBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture2D::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

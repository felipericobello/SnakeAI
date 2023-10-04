#pragma once
#include <Renderer.h>
#include <stb_image/stb_image.h>	

class Texture2D
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture2D(std::string& filepath);
	~Texture2D();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

};


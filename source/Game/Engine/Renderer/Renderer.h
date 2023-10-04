#ifndef RENDERER_H
#define RENDERER_H

#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>

class Renderer
{
public:
	Renderer() {};
	void Clear() const;
	void Draw(VertexArray* va, IndexBuffer* ib, Shader* shader);
};

#endif
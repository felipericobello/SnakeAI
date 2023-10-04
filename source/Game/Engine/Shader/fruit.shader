#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 uFruitProjectionModel;

void main()
{
	gl_Position = uFruitProjectionModel * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 uFruitColor;

void main()
{
	color = uFruitColor;
}